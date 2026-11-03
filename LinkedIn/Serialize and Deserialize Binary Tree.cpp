/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Example 1:

Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]
Example 2:

Input: root = []
Output: []
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "null";
        queue<TreeNode*> q;
        q.push(root);
        string res;
        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if(node) {
                res += to_string(node-> val) + ",";
                q.push(node-> left);
                q.push(node-> right);
            } else {
                res += "null,";
            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "null") return nullptr;

        stringstream ss(data);
        string token;
        getline(ss, token, ',');

        TreeNode *root = new TreeNode(stoi(token));
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if(!getline(ss, token, ',')) break;
            if(token != "null") {
                node-> left = new TreeNode(stoi(token));
                q.push(node-> left);
            }
            if(!getline(ss, token, ',')) break;
            if(token != "null") {
                node-> right = new TreeNode(stoi(token));
                q.push(node-> right);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
