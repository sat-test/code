/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
- Given target value is a floating point.
- You may assume k is always valid, that is: k ≤ total nodes.
- You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
Example:

Input: root = [4,2,5,1,3], target = 3.714286, and k = 2      4    / \   2   5  / \ 1   3  Output: [4,3]
*/


void dfs(BinaryTreeNode<int>* node, int k, double x,
         priority_queue<pair<double, int>>& pq) {
    if (node == nullptr) {
        return;
    }

    dfs(node->left, k, x, pq);

    pq.push({abs(node->data - x), node->data});
    if (pq.size() > k) {
        pq.pop();
    }

    dfs(node->right, k, x, pq);
}

vector<int> findClosestElement(BinaryTreeNode<int>* node, int k, double x) {
    priority_queue<pair<double, int>> pq;
    dfs(node, k, x, pq);

    vector<int> res;
    while (!pq.empty()) {
        res.push_back(pq.top().second);
        pq.pop();
    }

    return res;
}
