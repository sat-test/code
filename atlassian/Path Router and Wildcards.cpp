/*
Path Router + Wildcards
Design a path-based router that maps URL-like paths to associated values.
The router should support registering a path and retrieving the value associated with a path.
Operations
Implement the following operations:
addRoute(path, value)
getRoute(path)

1. addRoute(path, value)
Registers a path with a value.
Example:
addRoute("/home", "HomePage")
addRoute("/users", "UserPage")
addRoute("/users/profile", "ProfilePage")

2. getRoute(path)
Returns the value associated with the exact path.
Example:
getRoute("/home")
→ "HomePage"

getRoute("/users/profile")
→ "ProfilePage"

getRoute("/unknown")
→ null / not found
*/

class Node {
private:
    string content;

    // Exact path segment -> child
    unordered_map<string, Node*> children;

    // Child representing "*"
    Node* wildcard;

public:
    Node() {
        content = "";
        wildcard = nullptr;
    }

    bool hasChild(const string& key) {
        return children.find(key) != children.end();
    }

    Node* getChild(const string& key) {
        auto it = children.find(key);

        if (it == children.end()) {
            return nullptr;
        }

        return it->second;
    }

    void addChild(const string& key, Node* node) {
        children[key] = node;
    }

    Node* getWildcard() {
        return wildcard;
    }

    void setWildcard(Node* node) {
        wildcard = node;
    }

    void setContent(const string& value) {
        content = value;
    }

    string getContent() {
        return content;
    }
};


class Solution {
private:
    Node* root;

    vector<string> breakPath(const string& path) {
        stringstream ss(path);
        string part;
        vector<string> result;

        while (getline(ss, part, '/')) {
            if (!part.empty()) {
                result.push_back(part);
            }
        }

        return result;
    }

public:
    Solution() {
        root = new Node();
    }

    void addRoute(string path, string value) {

        vector<string> parts = breakPath(path);
        Node* curr = root;

        for (const string& part : parts) {
            if (part == "*") {
                if (curr->getWildcard() == nullptr) {
                    curr->setWildcard(new Node());
                }
                curr = curr->getWildcard();
            } else {
                if (!curr->hasChild(part)) {
                    curr->addChild(part, new Node());
                }
                curr = curr->getChild(part);
            }
        }
        curr->setContent(value);
    }

    string getRoute(string path) {

        vector<string> parts = breakPath(path);
        Node* curr = root;

        for (const string& part : parts) {
            // Exact match gets priority
            if (curr->hasChild(part)) {
                curr = curr->getChild(part);
            }
            // Otherwise use wildcard
            else if (curr->getWildcard() != nullptr) {
                curr = curr->getWildcard();
            }
            else {
                return "Not Found";
            }
        }
        return curr->getContent();
    }
};

int main() {
    Solution s;
    
    s.addRoute("/home", "HomePage");
    s.addRoute("/users", "UserPage");
    s.addRoute("/users/profile", "ProfilePage");
    s.addRoute("/users/*", "User");
    
    cout<<s.getRoute("/home")<<"\n";
    cout<<s.getRoute("/users/*")<<"\n";
    cout<<s.getRoute("/users/profile")<<"\n";
    cout<<s.getRoute("/unknown")<<"\n";
    
}
