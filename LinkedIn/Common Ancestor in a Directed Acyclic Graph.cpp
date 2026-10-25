/*
Suppose we have some input data describing a graph of relationships between parents and children over multiple generations. 
The data is formatted as a list of (parent, child) pairs, where each individual is assigned a unique positive integer identifier.


For example, in this diagram, 6 and 8 have common ancestors of 4 and 14.


              15
             / \
        14  13  21
        |   |
1   2   4   12
\ /   / | \ /
 3   5  8  9
  \ / \     \
   6   7     11


pairs = [
   (1, 3), (2, 3), (3, 6), (5, 6), (5, 7), (4, 5),
   (15, 21), (4, 8), (4, 9), (9, 11), (14, 4), (13, 12),
   (12, 9), (15, 13)
]

3: [1,2]
4: [14]
6: [3,5,1,2,4,14]
8:[4,14]



Write a function that takes this data and the identifiers of two individuals as inputs and returns true if and only if they share at least one ancestor.


Sample input and output:


hasCommonAncestor(pairs, 3, 8)   => false
hasCommonAncestor(pairs, 5, 8)   => true
hasCommonAncestor(pairs, 6, 8)   => true
hasCommonAncestor(pairs, 6, 9)   => true
hasCommonAncestor(pairs, 1, 3)   => false
hasCommonAncestor(pairs, 3, 1)   => false
hasCommonAncestor(pairs, 7, 11)  => true
hasCommonAncestor(pairs, 6, 5)   => true
hasCommonAncestor(pairs, 5, 6)   => true
hasCommonAncestor(pairs, 3, 6)   => true
hasCommonAncestor(pairs, 21, 11) => true


n: number of pairs in the input
*/

class Solution {
private:
    void traverse(unordered_map<int, vector<int>> &adj, int person, unordered_set<int> &s) {
        for(auto it: adj[person]) {
            if(s.find(it) == s.end()) {
                s.insert(it);
                traverse(adj, it, s); 
            }
        }
    }
    
    bool checkAlreadyTraverse(unordered_map<int, vector<int>> &adj, int person, unordered_set<int> &s, unordered_set<int> &visited) {
        if(s.find(person) != s.end()) {
            return true;
        }
        if (visited.find(person) != visited.end()) {
            return false;
        }
        visited.insert(person);
        for(auto it: adj[person]) {
            if(checkAlreadyTraverse(adj, it, s, visited)) {
                return true;
            }
        }
        return false;
    }
public:
    bool hasCommonAncestor(vector<vector<int>>& pairs, int person1, int person2) {
        unordered_map<int, vector<int>> adj;
        for(auto pair: pairs) {
            adj[pair[1]].push_back(pair[0]);
        }
        unordered_set<int> s;
        traverse(adj, person1, s);
        
        s.erase(person1);
        s.erase(person2);
        
        unordered_set<int> visited;
        return checkAlreadyTraverse(adj, person2, s, visited);
    }
};

int main() {
    Solution s;
    vector<vector<int>> pairs = {{1,3}, {2,3}, {3,6}, {5,6}, {5,7}, {4,5}, {15,21}, {4,8}, {4,9}, {9,11}, {14,4}, {13,12}, {12,9}, {15,13}};
    
    cout<<s.hasCommonAncestor(pairs, 3, 8)<<"\n";
    cout<<s.hasCommonAncestor(pairs, 5, 8)<<"\n"; 
    cout<<s.hasCommonAncestor(pairs, 6, 8)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 6, 9)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 1, 3)<<"\n";   
    cout<<s.hasCommonAncestor(pairs, 3, 1)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 7, 11)<<"\n"; 
    cout<<s.hasCommonAncestor(pairs, 6, 5)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 5, 6)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 3, 6)<<"\n";  
    cout<<s.hasCommonAncestor(pairs, 21, 11)<<"\n";
}
