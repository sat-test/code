/*
Given the root of a Binary Search Tree (BST) and an integer k, find the minimum absolute difference between k and the value of any node in the BST.

Examples:

Input: root = [10, 2, 11, 1, 5, N, N, N, N, 3, 6, N, 4], k = 13

Output: 2
Explanation: The node that has value nearest to k is 11. So, the minimum absolute difference is |11-13| = 2.
Input: root = [8, 1, 9, N, 4, N, 10, 3], k = 9

Output: 0
Explanation: The node that has value nearest to k is 9.  So, the minimum absolute difference is |9-9| = 0.
*/

/* Structure of a Binary Search Tree node
class Node {
   public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; */

int inf = 100005;

class Solution {
    int minDiffInBST(Node *node, int k) {
        if(node == nullptr) {
            return inf;
        }
        if(k < node-> data) {
            return min(node-> data - k, minDiffInBST(node-> left, k));
        } else {
            return min(k - node-> data, minDiffInBST(node-> right, k));
        }
    }
    
  public:
    int minDiff(Node *root, int k) {
        return minDiffInBST(root, k);
    }
};
