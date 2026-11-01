/*
TPS
a modified LFU cache. Instead of considering frequency for eviction, there is a mocked API which gives rank of the keys in the cache. This ranking is used for eviction.

Follow up - use LRU policy for keys with same rank

[Chat GPT Varient]
This is a variation of the LRU Cache problem, but instead of evicting the least recently used key, the cache evicts the key with the lowest rank returned by a mocked ranking API.

The follow-up adds an LRU policy when multiple keys have the same rank.
Interview question: Rank-Based Cache with LRU Tie-Breaker
Problem statement
Design and implement a fixed-capacity cache that supports the following operations:
- get(key): Returns the value associated with the key if it exists in the cache; otherwise, returns -1.
- put(key, value): Inserts a new key-value pair or updates an existing key.
- getRank(key): A mocked API that returns the rank of a key. A higher rank indicates that the key is more valuable to keep in the cache.
When the cache reaches its capacity and a new key needs to be inserted, the cache must evict the key with the lowest rank.
Follow-up
If multiple keys have the same lowest rank, evict the least recently used key among them.

*/

import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        System.out.println("========== Started ===========\n");

        RankBasedLRUCache insertionCache = new RankBasedLRUCache(2);
        insertionCache.put(1, 10);
        check("insertion and get", 10, insertionCache.get(1));

        insertionCache.put(1, 100);
        check("updating existing key", 100, insertionCache.get(1));

        RankBasedLRUCache rankEvictionCache = new RankBasedLRUCache(2);
        rankEvictionCache.put(1, 10); // rank 10
        rankEvictionCache.put(2, 20); // rank 20
        rankEvictionCache.put(4, 40); // evicts key 1, which has the lowest rank
        check("eviction by lowest rank", -1, rankEvictionCache.get(1));
        check("higher rank key retained", 20, rankEvictionCache.get(2));

        RankBasedLRUCache lruTieCache = new RankBasedLRUCache(2);
        lruTieCache.put(1, 10); // rank 10
        lruTieCache.put(3, 30); // rank 10; key 1 is now LRU
        check("get promotes within rank", 10, lruTieCache.get(1));
        lruTieCache.put(2, 20); // evicts key 3, the LRU key at rank 10
        check("LRU tie-breaking for equal ranks", -1, lruTieCache.get(3));
        check("recently used equal-rank key retained", 10, lruTieCache.get(1));

        RankBasedLRUCache missingCache = new RankBasedLRUCache(2);
        check("get a missing key", -1, missingCache.get(99));

        RankBasedLRUCache refillCache = new RankBasedLRUCache(1);
        refillCache.put(1, 10);
        refillCache.put(2, 20); // evicts key 1
        refillCache.put(3, 30); // inserts after eviction and evicts key 2
        check("inserting after eviction", 30, refillCache.get(3));
        check("previous key evicted after refill", -1, refillCache.get(2));

        System.out.println("========== Ended ===========\n");
    }

    private static void check(String testName, int expected, Integer actual) {
        if (actual == null || actual != expected) {
            throw new IllegalStateException(testName + " failed: expected " + expected + ", got " + actual);
        }
        System.out.println("PASS: " + testName);
    }
}

class Node {
    private int key;
    private int value;
    private Node left;
    private Node right;

    public Node(int key, int value, Node left, Node right) {
        this.key = key;
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }
}

class NodeList {
    private final Node head;
    private final Node tail;

    public NodeList() {
        head = new Node(-1, -1, null, null);
        tail = new Node(-1, -1, null, null);
        head.setRight(tail);
        tail.setLeft(head);
    }

    public void insertAtBeginning(Node node) {
        Node first = head.getRight();
        node.setLeft(head);
        node.setRight(first);
        head.setRight(node);
        first.setLeft(node);
    }

    public void deleteAtEnd() {
        Node last = tail.getLeft();
        if (last == head) {
            return;
        }

        Node newLast = last.getLeft();
        newLast.setRight(tail);
        tail.setLeft(newLast);
        last.setLeft(null);
        last.setRight(null);
    }

    public Node getLRUNode() {
        Node last = tail.getLeft();
        return last == head ? null : last;
    }

    public boolean isEmpty() {
        return head.getRight() == tail;
    }

    public void remove(Node node) {
        Node previous = node.getLeft();
        Node next = node.getRight();
        if (previous != null && next != null) {
            previous.setRight(next);
            next.setLeft(previous);
            node.setLeft(null);
            node.setRight(null);
        }
    }
}

class RankBasedLRUCache {
    private final int capacity;
    private final TreeMap<Integer, NodeList> rankToNodeList = new TreeMap<>();
    private final HashMap<Integer, Node> keyToNode = new HashMap<>();

    public RankBasedLRUCache(int capacity) {
        this.capacity = capacity;
    }

    public Integer get(int key) {
        Node node = keyToNode.get(key);
        if (node == null) {
            return -1;
        }

        int rank = rankApi(key);
        NodeList nodeList = rankToNodeList.get(rank);
        nodeList.remove(node);
        nodeList.insertAtBeginning(node);
        return node.getValue();
    }

    public void put(int key, int value) {
        int rank = rankApi(key);
        Node existingNode = keyToNode.get(key);

        if (existingNode != null) {
            existingNode.setValue(value);
            NodeList nodeList = rankToNodeList.get(rank);
            nodeList.remove(existingNode);
            nodeList.insertAtBeginning(existingNode);
            return;
        }

        if (capacity <= 0) {
            return;
        }

        if (keyToNode.size() == capacity) {
            evictLowestRankLRU();
        }

        Node node = new Node(key, value, null, null);
        rankToNodeList.computeIfAbsent(rank, ignored -> new NodeList()).insertAtBeginning(node);
        keyToNode.put(key, node);
    }

    private void evictLowestRankLRU() {
        Map.Entry<Integer, NodeList> lowestRankEntry = rankToNodeList.firstEntry();
        if (lowestRankEntry == null) {
            return;
        }

        int lowestRank = lowestRankEntry.getKey();
        NodeList lowestRankList = lowestRankEntry.getValue();
        Node lruNode = lowestRankList.getLRUNode();
        lowestRankList.remove(lruNode);
        keyToNode.remove(lruNode.getKey());
        if (lowestRankList.isEmpty()) {
            rankToNodeList.remove(lowestRank);
        }
    }

    private int rankApi(int key) {
        // Mocked rank API for practice. Lower rank means lower priority.
        Map<Integer, Integer> ranks = new HashMap<>();
        ranks.put(1, 10);
        ranks.put(2, 20);
        ranks.put(3, 10);
        ranks.put(4, 30);
        ranks.put(5, 20);
        ranks.put(6, 40);
        return ranks.getOrDefault(key, 0);
    }
}

