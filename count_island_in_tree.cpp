#include<bits/stdc++.h>

using namespace std;

// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;
    
//     TreeNode(int value) {
//         val = value;
//         left = nullptr;
//         right = nullptr;
//     }
// };


void traverse(TreeNode* node, vector<TreeNode*> &vec) {
    if(node == nullptr) {
        return;
    }
    if(node-> val == 0) {
        vec.push_back(node);
        return;
    } 
    traverse(node-> left, vec);
    traverse(node-> right, vec);
}

int findIsland(TreeNode* root) {
    stack<TreeNode*> stk;
    stk.push(root);
    int res = 0;
    while(!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();
        if(node-> val == 1) {
            ++res;
            vector<TreeNode*> vec;
            traverse(node, vec);
            for(int i=0; i<vec.size(); i++) {
                stk.push(vec[i]);
            }
        } else {
            if(node-> left) {
                stk.push(node-> left);
            }   
            if(node-> right) {
                stk.push(node-> right);
            }
        }
    }
    return res;
}

int main() {
    TreeNode* root = new TreeNode(0);
    // root->left = new TreeNode(1);
    // root->right = new TreeNode(0);
    // root->left->left = new TreeNode(1);
    // root->left->right = new TreeNode(1);
    // root->right->left = new TreeNode(1);
    // root->right->right = new TreeNode(1);
    root-> left = new TreeNode(1);
    root-> right = new TreeNode(0);
    root-> left-> left = new TreeNode(1);
    root-> left-> right = new TreeNode(1);
    root-> left-> left-> left = new TreeNode(0);
    root-> left-> right-> left = new TreeNode(0);
    root-> left-> right-> right = new TreeNode(1);
    root-> left-> left-> left-> left = new TreeNode(1);
    root-> left-> left-> left-> right = new TreeNode(1);
    root-> right-> right = new TreeNode(0);
    root-> right-> right-> left = new TreeNode(1);
    root-> right-> right-> right = new TreeNode(1);
    root-> right-> right-> left-> left = new TreeNode(0);
    root-> right-> right-> right-> right = new TreeNode(0);
    int res = findIsland(root);
    cout<<res<<"\n";
}

/*

#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Helper function to traverse and mark all connected 1s as visited
void dfs(TreeNode* node) {
    if (node == nullptr || node->val == 0) {
        return;
    }

    // Mark the node as visited by changing its value to 0
    node->val = 0;

    // Traverse left and right subtrees
    dfs(node->left);
    dfs(node->right);
}

int findIsland(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int islands = 0;
    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();

        if (node->val == 1) {
            // We found a new island, perform DFS to mark all connected 1s
            ++islands;
            dfs(node);  // Mark all nodes in this island as visited
        }

        // Continue the traversal
        if (node->left) {
            stk.push(node->left);
        }
        if (node->right) {
            stk.push(node->right);
        }
    }

    return islands;
}

int main() {
    // Example tree
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(1);
    root->right = new TreeNode(0);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(1);
    root->right->left = new TreeNode(1);
    root->right->right = new TreeNode(1);

    int res = findIsland(root);
    cout << "Number of islands: " << res << endl;  // Expected output: 3
}

*/
