/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).
Example 1:
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
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
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        deque<TreeNode*> stk;
        stk.push_back(root);
        vector<vector<int>> res;
        
        if(root == NULL)
            return res;
        
        bool flag = true;
        while(!stk.empty()){
            int n = stk.size();
            if(flag){
                vector<int> tmp;
                for(int i=0; i<n; i++){
                    TreeNode *node = stk.back();
                    stk.pop_back();
                    tmp.push_back(node->val);
                    if(node->left)
                        stk.push_front(node->left);
                    if(node->right)
                        stk.push_front(node->right);
                 }
                res.push_back(tmp);
            }
            else{
                vector<int> tmp;
                for(int i=0; i<n; i++){
                    TreeNode *node = stk.front();
                    stk.pop_front();
                    tmp.push_back(node->val);
                    if(node->right)
                        stk.push_back(node->right);
                    if(node->left)
                        stk.push_back(node->left);
                 }
                 res.push_back(tmp);
            }
            flag = !flag;
        }
        return res;
    }
};
