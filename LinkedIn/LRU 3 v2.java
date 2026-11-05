
import java.util.*;
import java.util.concurrent.TimeUnit;

class Node {
    private final int key;
    private int value;
    private Node left;
    private Node right;
    private Long expiry;

    public Node(int key, int value) {
        this(key, value, null);
    }

    public Node(int key, int value, Long expiry) {
        this.key = key;
        this.value = value;
        this.expiry = expiry;
    }

    public int getKey() {
        return key;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Node getLeftNode() {
        return left;
    }

    public Node getRightNode() {
        return right;
    }

    public void setLeftNode(Node node) {
        this.left = node;
    }

    public void setRightNode(Node node) {
        this.right = node;
    }

    public Long getExpiry() {
        return expiry;
    }

    public void setExpiry(Long expiry) {
        this.expiry = expiry;
    }

    public boolean hasExpiry() {
        return expiry != null;
    }
}

// Doubly linked list
class NodeList {
    private final Node head;
    private final Node tail;

    public NodeList() {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head.setRightNode(tail);
        tail.setLeftNode(head);
    }

    // Add node as most recently used
    public void addNodeAtBeginning(Node node) {
        node.setLeftNode(head);
        node.setRightNode(head.getRightNode());

        head.getRightNode().setLeftNode(node);
        head.setRightNode(node);
    }

    public void deleteNode(Node node) {
        node.getLeftNode().setRightNode(node.getRightNode());
        node.getRightNode().setLeftNode(node.getLeftNode());

        node.setLeftNode(null);
        node.setRightNode(null);
    }

    // Least recently used node
    public Node getLRUNode() {
        return tail.getLeftNode();
    }
}

class LRUCache {

    private static final long NO_EXPIRY = -1L;

    private final int capacity;

    // Key -> Node
    private final Map<Integer, Node> nodeMap;

    // Expiry timestamp -> Keys
    private final TreeMap<Long, Set<Integer>> expiryKeyMap;

    // LRU doubly linked list
    private final NodeList nodes;

    private long getHits;
    private long getMisses;

    public LRUCache(int capacity) {

        if (capacity <= 0) {
            throw new IllegalArgumentException(
                "Capacity must be greater than zero"
            );
        }

        this.capacity = capacity;
        this.nodeMap = new HashMap<>();
        this.expiryKeyMap = new TreeMap<>();
        this.nodes = new NodeList();

        this.getHits = 0;
        this.getMisses = 0;
    }

    // -----------------------------------
    // GET
    // -----------------------------------

    public synchronized Integer get(int key) {

        Node node = nodeMap.get(key);

        if (node == null) {
            getMisses++;
            return -1;
        }

        if (isExpired(node)) {
            removeNode(node);
            getMisses++;
            return -1;
        }

        getHits++;

        // Move accessed node to MRU position
        nodes.deleteNode(node);
        nodes.addNodeAtBeginning(node);

        return node.getValue();
    }

    // -----------------------------------
    // PUT WITHOUT TTL
    // -----------------------------------

    public synchronized void put(int key, int value) {

        putInternal(key, value, null);
    }

    // -----------------------------------
    // PUT WITH TTL (milliseconds)
    // -----------------------------------

    public synchronized void put(
        int key,
        int value,
        long ttlMillis
    ) {

        if (ttlMillis < 0) {
            throw new IllegalArgumentException(
                "TTL cannot be negative"
            );
        }

        long expiry = System.nanoTime()
                + TimeUnit.MILLISECONDS.toNanos(ttlMillis);

        putInternal(key, value, expiry);
    }

    // -----------------------------------
    // COMMON PUT LOGIC
    // -----------------------------------

    private void putInternal(
        int key,
        int value,
        Long expiry
    ) {

        // Remove expired entries first
        cleanupExpiredEntries();

        Node node = nodeMap.get(key);

        if (node != null) {

            // Remove old expiry registration
            removeExpiryRegistration(node);

            // Update existing node
            node.setValue(value);
            node.setExpiry(expiry);

            // Move to MRU position
            nodes.deleteNode(node);
            nodes.addNodeAtBeginning(node);

        } else {

            // Evict LRU if cache is full
            if (nodeMap.size() >= capacity) {

                Node lruNode = nodes.getLRUNode();

                removeNode(lruNode);
            }

            // Insert new node
            node = new Node(key, value, expiry);

            nodeMap.put(key, node);
            nodes.addNodeAtBeginning(node);
        }

        // Register new expiry
        if (expiry != null) {
            registerExpiry(key, expiry);
        }
    }

    // -----------------------------------
    // REGISTER EXPIRY
    // -----------------------------------

    private void registerExpiry(int key, long expiry) {

        expiryKeyMap
            .computeIfAbsent(expiry, k -> new HashSet<>())
            .add(key);
    }

    // -----------------------------------
    // REMOVE EXPIRY REGISTRATION
    // -----------------------------------

    private void removeExpiryRegistration(Node node) {

        if (!node.hasExpiry()) {
            return;
        }

        Long expiry = node.getExpiry();

        Set<Integer> keys = expiryKeyMap.get(expiry);

        if (keys != null) {

            keys.remove(node.getKey());

            if (keys.isEmpty()) {
                expiryKeyMap.remove(expiry);
            }
        }
    }

    // -----------------------------------
    // CLEANUP EXPIRED ENTRIES
    // -----------------------------------

    private void cleanupExpiredEntries() {

        long now = System.nanoTime();

        while (!expiryKeyMap.isEmpty()) {

            Map.Entry<Long, Set<Integer>> entry =
                expiryKeyMap.firstEntry();

            long expiry = entry.getKey();

            // Earliest expiry is still in the future
            if (now - expiry < 0) {
                break;
            }

            // Remove expired timestamp bucket
            Set<Integer> expiredKeys =
                expiryKeyMap.pollFirstEntry().getValue();

            for (Integer key : expiredKeys) {

                Node node = nodeMap.get(key);

                if (node != null &&
                    node.hasExpiry() &&
                    node.getExpiry().equals(expiry)) {

                    nodes.deleteNode(node);
                    nodeMap.remove(key);
                }
            }
        }
    }

    // -----------------------------------
    // CHECK EXPIRY
    // -----------------------------------

    private boolean isExpired(Node node) {

        if (!node.hasExpiry()) {
            return false;
        }

        return System.nanoTime() - node.getExpiry() >= 0;
    }

    // -----------------------------------
    // REMOVE NODE
    // -----------------------------------

    private void removeNode(Node node) {

        nodes.deleteNode(node);

        nodeMap.remove(node.getKey());

        removeExpiryRegistration(node);
    }

    // -----------------------------------
    // CACHE STATISTICS
    // -----------------------------------

    public synchronized long getHits() {
        return getHits;
    }

    public synchronized long getMisses() {
        return getMisses;
    }

    public synchronized double getHitRatio() {

        long total = getHits + getMisses;

        if (total == 0) {
            return 0.0;
        }

        return (double) getHits / total;
    }

    public synchronized double getMissRatio() {

        long total = getHits + getMisses;

        if (total == 0) {
            return 0.0;
        }

        return (double) getMisses / total;
    }

    public synchronized int size() {
        return nodeMap.size();
    }
}

// -----------------------------------
// MAIN
// -----------------------------------

public class Main {

    public static void main(String[] args) throws Exception {

        // Test 1: Basic LRU
        System.out.println("----- LRU TEST -----");

        LRUCache cache = new LRUCache(2);

        cache.put(1, 100);
        cache.put(2, 200);

        System.out.println(cache.get(1)); // 100

        cache.put(3, 300);

        System.out.println(cache.get(2)); // -1
        System.out.println(cache.get(1)); // 100
        System.out.println(cache.get(3)); // 300

        // Test 2: TTL
        System.out.println("----- TTL TEST -----");

        cache.put(4, 400, 1000);

        System.out.println(cache.get(4)); // 400

        Thread.sleep(1200);

        System.out.println(cache.get(4)); // -1

        // Test 3: Expired entry should not occupy capacity
        System.out.println("----- CAPACITY TEST -----");

        LRUCache cache2 = new LRUCache(2);

        cache2.put(1, 100, 1000);
        cache2.put(2, 200);

        Thread.sleep(1200);

        cache2.put(3, 300);

        System.out.println(cache2.size()); // 2
        System.out.println(cache2.get(1));  // -1
        System.out.println(cache2.get(2));  // 200
        System.out.println(cache2.get(3));  // 300

        // Test 4: Updating TTL
        System.out.println("----- TTL UPDATE TEST -----");

        LRUCache cache3 = new LRUCache(2);

        cache3.put(10, 100, 1000);
        cache3.put(10, 200, 5000);

        Thread.sleep(1200);

        System.out.println(cache3.get(10)); // 200

        // Test 5: Statistics
        System.out.println("----- STATISTICS -----");

        System.out.println("Hits: " + cache.getHits());
        System.out.println("Misses: " + cache.getMisses());
        System.out.println("Hit Ratio: " + cache.getHitRatio());
        System.out.println("Miss Ratio: " + cache.getMissRatio());
    }
}
