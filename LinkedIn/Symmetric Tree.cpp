/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
Example 1:

Input: root = [1,2,2,3,4,4,3]
Output: true
Example 2:

Input: root = [1,2,2,null,3,null,3]
Output: false
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    bool isSymmetric(TreeNode *ls, TreeNode *rs) {
        if(ls == nullptr && rs == nullptr) {
            return true;
        }
        if(ls == nullptr || rs == nullptr) {
            return false;
        }
        if(ls-> val != rs-> val) {
            return false;
        }
        return isSymmetric(ls-> left, rs-> right) && isSymmetric(ls-> right, rs-> left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root-> left, root-> right);
    }
};
