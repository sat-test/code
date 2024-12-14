/*
The boundary of a binary tree is the concatenation of the root, the left boundary, the leaves ordered from left-to-right, and the reverse order of the right boundary.

The left boundary is the set of nodes defined by the following:

The root node's left child is in the left boundary. If the root does not have a left child, then the left boundary is empty.
If a node in the left boundary and has a left child, then the left child is in the left boundary.
If a node is in the left boundary, has no left child, but has a right child, then the right child is in the left boundary.
The leftmost leaf is not in the left boundary.
The right boundary is similar to the left boundary, except it is the right side of the root's right subtree. Again, the leaf is not part of the right boundary, and the right boundary is empty if the root does not have a right child.

The leaves are nodes that do not have any children. For this problem, the root is not a leaf.

Given the root of a binary tree, return the values of its boundary.

Input: root = [1,null,2,3,4]
Output: [1,3,4,2]
Explanation:
- The left boundary is empty because the root does not have a left child.
- The right boundary follows the path starting from the root's right child 2 -> 4.
  4 is a leaf, so the right boundary is [2].
- The leaves from left to right are [3,4].
Concatenating everything results in [1] + [] + [3,4] + [2] = [1,3,4,2].

https://leetcode.com/problems/boundary-of-binary-tree/
https://leetcode.ca/2017-05-28-545-Boundary-of-Binary-Tree/

*/

void dfs(TreeNode *node, vector<int> &vec, int i) {
    if(!node) {
        return;
    }
    if(i == 0) {
        if(node-> left != node-> right) {
            vec.push_back(node-> val);
            if(node-> left) {
                dfs(node-> left, vec, i);
            } else {
                dfs(node-> right, vec, i);
            }
        } 
    } else if(i == 1) {
        if(node-> left == node-> right) {
            vec.push_back(node-> val);
        } else {
            dfs(node-> left, vec, i);
            dfs(node-> right, vec, i);
        }
    } else if(i == 2) {
        if(node-> left != node-> right) {
            vec.push_back(node-> val);
        }
        if(node-> right) {
            dfs(node-> right, vec, i);
        } else {
            dfs(node-> left, vec, i);
        }
    }
}

vector<int> solve(TreeNode* root) {
    vector<int> res = {root-> val};
    if(root-> left == root-> right) {
        return res;
    }
    dfs(root-> left, res, 0);
    dfs(root, res, 1);
    dfs(root-> right, res, 2);
    return res;
}

void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    
   // Test Case 1: Single Node Tree
    TreeNode* root1 = new TreeNode(1);
    vector<int> result1 = solve(root1);
    cout << "Test Case 1: ";
    printVector(result1); // Expected: [1]

    // Test Case 2: Full Binary Tree
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->right->left = new TreeNode(6);
    root2->right->right = new TreeNode(7);
    vector<int> result2 = solve(root2);
    cout << "Test Case 2: ";
    printVector(result2); // Expected: [1, 2, 4, 5, 6, 7, 3]

    // Test Case 3: Left-Skewed Tree
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->left->left = new TreeNode(3);
    root3->left->left->left = new TreeNode(4);
    vector<int> result3 = solve(root3);
    cout << "Test Case 3: ";
    printVector(result3); // Expected: [1, 2, 3, 4]

    // Test Case 4: Right-Skewed Tree
    TreeNode* root4 = new TreeNode(1);
    root4->right = new TreeNode(2);
    root4->right->right = new TreeNode(3);
    root4->right->right->right = new TreeNode(4);
    vector<int> result4 = solve(root4);
    cout << "Test Case 4: ";
    printVector(result4); // Expected: [1, 4, 3, 2]

    // Test Case 5: Mixed Tree
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    root5->left->left = new TreeNode(3);
    root5->right = new TreeNode(4);
    root5->right->right = new TreeNode(5);
    vector<int> result5 = solve(root5);
    cout << "Test Case 5: ";
    printVector(result5); // Expected: [1, 2, 3, 5, 4]

    return 0;
}
