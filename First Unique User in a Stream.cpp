/*
Problem Statement
You're given a stream of user IDs visiting a website. Implement two functions:

void PostAddUser(int userId): Adds a new user ID to the stream.
int GetFirstOneTimeUser(): Returns the first user ID that has visited exactly once and is still the first such user in order. If no such user exists, return -1.
Example Usage:

PostAddUser(1);
PostAddUser(2);
PostAddUser(3);
PostAddUser(1);
cout << GetFirstOneTimeUser(); // Output: 2
PostAddUser(2);
cout << GetFirstOneTimeUser(); // Output: 3
PostAddUser(3);
cout << GetFirstOneTimeUser(); // Output: -1
*/

class Node {
public:
    int value;
    Node *prev;
    Node *next;
    Node(int val) {
        value = val;
        prev = nullptr;
        next = nullptr;
    }
};

class WebsiteTracker {
private:
    Node *head;
    Node *tail;
    
    unordered_map<int, Node*> nodeMap;
    unordered_map<int, int> visitCount;
    
    void addNode(Node *node) {
        node->next = tail;
        node->prev = tail->prev;
        tail->prev->next = node;
        tail->prev = node;
    }
    
    void removeNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
public:
    WebsiteTracker() {
        head = new Node(-1);
        tail = new Node(-1);
        head-> next = tail;
        tail-> prev = head;
    }
    
    void postAddUser(int userId) {
        visitCount[userId]++;
        if (visitCount[userId] == 1) {
            Node *newNode = new Node(userId);
            addNode(newNode);
            nodeMap[userId] = newNode;
        } else if (visitCount[userId] == 2) {
            Node *node = nodeMap[userId];
            removeNode(node);
            delete node;
            nodeMap.erase(userId);
        }
    }
    
    int getFirstOneTimeUser() {
        if (head->next == tail) {
            return -1;
        }
        return head->next->value;
    }
};

int main() {
    WebsiteTracker wt;
    wt.postAddUser(1);
    wt.postAddUser(2);
    wt.postAddUser(3);
    wt.postAddUser(1);
    cout << wt.getFirstOneTimeUser() << endl; 
    wt.postAddUser(2);
    cout << wt.getFirstOneTimeUser() << endl; 
    wt.postAddUser(3);
    cout << wt.getFirstOneTimeUser() << endl; 
}
