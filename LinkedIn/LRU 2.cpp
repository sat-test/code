class Node {
    private Integer key;
    private Integer value;
    private Node left;
    private Node right;
    private Long expiry;
    
    public Node() {
        this.key = -1;
        this.value = -1;
        this.expiry = -1L;
        this.left = null;
        this.right = null;
    }
    
    public Node(int key, int value) {
        this.key = key;
        this.value = value;
        this.expiry = -1L;
        this.left = null;
        this.right = null;
    }
    
    public Node(int key, int value, long expiry) {
        this.key = key;
        this.value = value;
        this.expiry = expiry;
        this.left = null;
        this.right = null;
    }
    
    public int getKey() {
        return this.key;
    }
    
    public int getValue() {
        return this.value;
    }
    
    public Node getLeftNode() {
        return this.left;
    }
    
    public Node getRightNode() {
        return this.right;
    }
    
    public void setValue(Integer value) {
        this.value = value;
    }
    
    public void setLeftNode(Node node) {
        this.left = node;
    }
    
    public void setRightNode(Node node) {
        this.right = node;
    }
    
    public Boolean hasExpiry() {
        return expiry != -1L;
    }
    
    public Long getExpiry() {
        return this.expiry;
    }
    
    public void setExpiry(Long expiry) {
        this.expiry = expiry;
    }
}

class NodeList{
    private Node head;
    private Node tail;
    private int capacity;
    
    public NodeList() {
        head = new Node();
        tail = new Node();
        head.setRightNode(tail);
        tail.setLeftNode(head);
    }
    
    public void addNodeAtBegining(Node node) {
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
    
    public Node getTailNode() {
        return this.tail;
    }
}

class LRUCache {
    private NodeList nodes;
    private NodeList nodesWithExpiry;
    private Map<Integer, Node> nodeMap;
    private Integer capacity;
    
    public LRUCache(Integer capacity) {
        this.nodes = new NodeList();
        this.nodeMap = new HashMap<>();
        this.capacity = capacity;
    }
    
    public synchronized Integer get(int key) {
        if(!nodeMap.containsKey(key)) {
            return -1;
        }
        
        Node node = nodeMap.get(key);
        if (isExpired(node)) {
            removeNode(node);
            return -1;
        }
        
        nodes.deleteNode(node);
        nodes.addNodeAtBegining(node);
        
        return node.getValue();
    }
    
    public synchronized void put(Integer key, Integer value) {
        putInternal(key, value, -1L);
    }
    
    public synchronized void put(Integer key, Integer value, Long ttlMillis) {
        long expiry = System.currentTimeMillis() + ttlMillis;
        putInternal(key, value, expiry); 
    }
    
    private void putInternal(Integer key, Integer value, Long expiry) {
        if(!nodeMap.containsKey(key)) {
            Node node = new Node(key, value, expiry);
            nodeMap.put(key, node);
            nodes.addNodeAtBegining(node);
        } else {
            Node node = nodeMap.get(key);
            node.setValue(value);
            node.setExpiry(expiry);
            nodes.deleteNode(node);
            nodes.addNodeAtBegining(node);
        }
        if(nodeMap.size() > capacity) {
            Node node = nodes.getTailNode().getLeftNode();
            removeNode(node);
        }
    }
    
    private boolean isExpired(Node node) {
        return node.hasExpiry() && System.currentTimeMillis() >= node.getExpiry();
    }
    
    private void removeNode(Node node) {
        nodes.deleteNode(node);
        nodeMap.remove(node.getKey());
    }
}

public class Main {
    public static void print(String str, int res) {
        System.out.println(str + " : " + res);
    }
    public static void main(String[] args) throws InterruptedException {
        Integer res;
        LRUCache cache = new LRUCache(2);
        
        cache.put(1, 10);
        cache.put(2, 20);
        
        res = cache.get(1);
        print("1", res);
        
        cache.put(3, 30); 
        
        res = cache.get(2); 
        print("2", res);
        
        res = cache.get(1);
        print("1", res);
        
        res = cache.get(3);
        print("3", res);
        
        // TTL behavior
        cache.put(4, 40, 1000L);

        res = cache.get(4);
        print("4 before expiry", res);

        Thread.sleep(1500L);

        res = cache.get(4);
        print("4 after expiry", res);
        
        LRUCache concurrentCache = new LRUCache(100);

        int numberOfThreads = 10;
        int operationsPerThread = 1000;
        
        Thread[] threads = new Thread[numberOfThreads];
        for (int i = 0; i < numberOfThreads; i++) {
            final int threadId = i;
            threads[i] = new Thread(() -> {
                for (int j = 0; j < operationsPerThread; j++) {
                    int key = (j % 100) + (threadId * 100);
                    int value = key * 10;
                    concurrentCache.put(key, value);
                    concurrentCache.get(key);
                    concurrentCache.put(key, value, 5000L);
                }
            });
            threads[i].start();
        }
        
        for (Thread thread : threads) {
            thread.join();
        }
        
        System.out.println("All threads completed successfully.");

        // Verify cache remains usable
        concurrentCache.put(10000, 100000);

        res = concurrentCache.get(10000);
        print("10000 after concurrent operations", res);
    }
}
