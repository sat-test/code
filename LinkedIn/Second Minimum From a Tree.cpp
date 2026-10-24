/** 
* A tournament tree is a binary tree 
* where the parent is the minimum of the two children. 
* Given a tournament tree find the second minimum value in the tree. 
* A node in the tree will always have 2 or 0 children. 
* Also all leaves will have distinct and unique values. 
*         2 
*      /    \ 
*     2      3 
*    / \    /  \    
*   4   2   5   3 
* 
* In this given tree the answer is 3. 
*/

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int value, Node* left = nullptr, Node* right = nullptr)
        : value(value), left(left), right(right) {}
};

class Solution {
public:
    void dfs(Node *node, int &mini, int &secondMini) {
        if(node == nullptr) {
            return;
        }
        int val = node-> value;
        if(val < mini) {
            secondMini = mini;
            mini = val;
        } else if(val > mini && val < secondMini) {
            secondMini = val;
        }
        dfs(node-> left, mini, secondMini);
        dfs(node-> right, mini, secondMini);
    }
    int secondMin(Node* root) {
        int mini = INT_MAX;
        int secondMini = INT_MAX;
        dfs(root, mini, secondMini);
        return secondMini == INT_MAX ? -1 : secondMini;;
    }
};
