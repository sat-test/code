/*
Problem statement
You are given a binary tree with ‘N’ nodes. Each node has an integer value associated with it. Your task is to print the leaf nodes and then remove these leaf nodes. Now, print the new leaf nodes and repeat the process until the tree becomes empty.

Note:
You don’t require to remove the leaf nodes. Just print the values in the required order.

The leaf nodes must be printed in a left to right order.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 100
1 <= N <= 10^5
-10^9 <= node data <= 10^9, (where node data != -1).

Time Limit: 1 sec
Sample Input 1:
1
6 -3 3 -1 -1 -1 -1
Sample Output 1:
-3 3
6
Explanation For Sample Output 1:
For the first test case, the given binary tree is depicted below.
*/

#include <bits/stdc++.h> 
/*************************************************************
 
    Following is the BinaryTreeNode class structure

    class BinaryTreeNode {
    public : 
        T data;
        BinaryTreeNode<T> *left;
        BinaryTreeNode<T> *right;

        BinaryTreeNode(T data) {
            this -> data = data;
            left = NULL;
            right = NULL;
        }
    };

*************************************************************/

int traverse(BinaryTreeNode<int> *node, vector<vector<int>> &res) {
    if(node == nullptr) {
        return -1;
    }
    int l = traverse(node-> left, res);
    int r = traverse(node-> right, res);
    int ind = max(l, r) + 1;
    int sz = res.size()-1;
    if(ind > sz) {
        res.push_back({node-> data});
    } else {
        res[ind].push_back(node-> data);
    }
    return ind;
}

vector<vector<int>> collectLeaves(BinaryTreeNode<int> *root) {
	vector<vector<int>> res;
    traverse(root, res);
    return res;
}
