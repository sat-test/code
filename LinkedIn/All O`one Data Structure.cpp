/*
Design a data structure to store the strings' count with the ability to return the strings with minimum and maximum counts.

Implement the AllOne class:

AllOne() Initializes the object of the data structure.
inc(String key) Increments the count of the string key by 1. If key does not exist in the data structure, insert it with count 1.
dec(String key) Decrements the count of the string key by 1. If the count of key is 0 after the decrement, remove it from the data structure. It is guaranteed that key exists in the data structure before the decrement.
getMaxKey() Returns one of the keys with the maximal count. If no element exists, return an empty string "".
getMinKey() Returns one of the keys with the minimum count. If no element exists, return an empty string "".
Note that each function must run in O(1) average time complexity.
*/

class Node {
public:
    int rank;
    unordered_set<string> keys;
    Node* left;
    Node* right;

    Node(int rank) {
        this-> rank = rank;
        left = nullptr;
        right = nullptr;
    }
};

class TreeNodes {
public:
    Node *head;
    Node *tail;

    TreeNodes() {
        head = new Node(-1);
        tail = new Node(-1);
        head-> right = tail;
        tail-> left = head;
    }

    void insertBetween(Node* leftNode, Node* rightNode, Node *newNode) {
        newNode-> left = leftNode;
        newNode-> right = rightNode;
        leftNode-> right = newNode;
        rightNode-> left = newNode;
    }

    void removeNode(Node *node) {
        node-> left-> right = node-> right;
        node-> right-> left = node-> left;
        delete node;
    }
};

class AllOne {
private:
    TreeNodes list;
    unordered_map<string, Node*> stringRankMap;
public:
  
    AllOne() {
        
    }
    
    void inc(string key) {
        if(stringRankMap.find(key) == stringRankMap.end()) {
            Node *first = list.head-> right;
            if(first == list.tail || first-> rank != 1) {
                Node *newNode = new Node(1);
                list.insertBetween(list.head, first, newNode);
                first = newNode;
            }
            first-> keys.insert(key);
            stringRankMap[key] = first;
            return;
        }

        Node *current = stringRankMap[key];
        int nextRank = current-> rank + 1;
        Node *nextNode = current-> right;

        if(nextNode == list.tail || nextNode-> rank != nextRank) {
            Node *newNode = new Node(nextRank);
            list.insertBetween(current, nextNode, newNode);
            nextNode = newNode;
        }

        nextNode-> keys.insert(key);
        stringRankMap[key] = nextNode;

        current->keys.erase(key);
        if(current-> keys.empty()) {
            list.removeNode(current);
        }
    }
    
    void dec(string key) {
        Node *current = stringRankMap[key];
        int currentRank = current-> rank;

        if(currentRank == 1) {
            current-> keys.erase(key);
            stringRankMap.erase(key);

            if(current-> keys.empty()) {
                list.removeNode(current);
            }
            return;
        }

        int prevRank = currentRank - 1;
        Node *prevNode = current-> left;

        if(prevNode == list.head || prevNode-> rank != prevRank) {
            Node *newNode = new Node(prevRank);
            list.insertBetween(prevNode, current, newNode);
            prevNode = newNode;
        }

        prevNode-> keys.insert(key);
        stringRankMap[key] = prevNode;

        current-> keys.erase(key);

        if(current-> keys.empty()) {
            list.removeNode(current);
        }
    }
    
    string getMaxKey() {
        if(list.tail-> left == list.head) {
            return "";
        }
        return *(list.tail-> left-> keys.begin());
    }
    
    string getMinKey() {
        if(list.head-> right == list.tail) {
            return "";
        }
        return *(list.head-> right-> keys.begin());
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
