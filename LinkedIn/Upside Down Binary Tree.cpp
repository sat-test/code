/*
Problem statement
You are given a rooted binary tree. In this binary tree, all the right nodes are either a leaf node with a sibling (left node sharing the same parent node) or empty. Your task is to flip this tree upside down such that all right nodes turn into left leaf nodes.

You are given the 'ROOT' of the binary tree. Your task is to return the new 'ROOT' after turning the tree upside down.

For Example:
Tree = [5, 4, 3, 1, 2, -1, -1, -1, -1, -1, -1]

 Upside down Tree :

ANS = [1, 2, 4, -1, -1, 3, 5, -1, -1, -1, -1]

*/

#include <bits/stdc++.h> 
/*************************************************************
 
    Following is the Binary Tree node structure

    template <typename T>
    class TreeNode {
    public : 
        T data;
        TreeNode<T> *left;
        TreeNode<T> *right;

        BinaryTreeNode(T data) {
            this -> data = data;
            left = NULL;
            right = NULL;
        }
    };

*************************************************************/

TreeNode<int>* flipTree(TreeNode<int> *root){
	if(root == nullptr || root-> left == nullptr) {
        return root;
    }

    TreeNode<int>* newNode = flipTree(root->left);
    root-> left-> right = root;
    root-> left-> left = root-> right;
    root-> left = nullptr;
    root-> right = nullptr;
    return newNode;
}
