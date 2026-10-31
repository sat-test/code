class Node {
    private Integer key;
    private Integer value;
    private Node left;
    private Node right;
    
    public Node() {
        this.key = -1;
        this.value = -1;
        this.left = null;
        this.right = null;
    }
    
    public Node(int key, int value) {
        this.key = key;
        this.value = value;
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
    private Map<Integer, Node> nodeMap;
    private Integer capacity;
    
    public LRUCache(Integer capacity) {
        this.nodes = new NodeList();
        this.nodeMap = new HashMap<>();
        this.capacity = capacity;
    }
    
    Integer get(int key) {
        if(!nodeMap.containsKey(key)) {
            return -1;
        }
        Node node = nodeMap.get(key);
        nodes.deleteNode(node);
        nodes.addNodeAtBegining(node);
        return node.getValue();
    }
    
    void put(Integer key, Integer value) {
        if(!nodeMap.containsKey(key)) {
            Node node = new Node(key, value);
            nodeMap.put(key, node);
            nodes.addNodeAtBegining(node);
        } else {
            Node node = nodeMap.get(key);
            node.setValue(value);
            nodes.deleteNode(node);
            nodes.addNodeAtBegining(node);
        }
        if(nodeMap.size() > capacity) {
            Node node = nodes.getTailNode().getLeftNode();
            nodes.deleteNode(node);
            nodeMap.remove(node.getKey());
        }
    }
}

public class Main {
    public static void print(String str, int res) {
        System.out.println(str + " : " + res);
    }
    public static void main(String[] args) {
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
    }
}
