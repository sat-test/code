/*
https://leetcode.com/discuss/post/6597723/uber-sde-2-interview-hard-question-by-an-ip9c/
[QuadTree Compression of a Matrix]
Problem Statement
A QuadTree is a tree data structure in which each internal node is either a leaf node or has exactly four children. QuadTrees are often used to partition a two-dimensional space by recursively subdividing it into four quadrants or regions.

Given an n x n matrix of integers, compress it using a QuadTree. A region can be compressed into a single value if all elements in that region are the same.

Example
Input:
|2 | 2 |3 |3|
|2 | 2 |3 |3|
|4 | 2 |5 |5|
|2 | 3 |5 |5|

output:
| | |
| 2 | 3 |
| | |
| 4 | 2 | 5 |
| 2 | 3 | |
*/

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    bool isLeaf;
    int val; 
    vector<Node*> children; 

    Node(int v) : isLeaf(true), val(v) {}
    Node(vector<Node*> ch) : isLeaf(false), val(-1), children(ch) {}
};

bool isUniform(const vector<vector<int>>& grid, int x, int y, int size, int& val) {
    val = grid[x][y];
    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            if (grid[i][j] != val)
                return false;
        }
    }
    return true;
}

Node* compress(const vector<vector<int>>& grid, int x, int y, int size) {
    int val;
    if (isUniform(grid, x, y, size, val)) {
        return new Node(val);
    }

    int half = size / 2;
    vector<Node*> children;
    children.push_back(compress(grid, x, y, half));                  
    children.push_back(compress(grid, x, y + half, half));          
    children.push_back(compress(grid, x + half, y, half));           
    children.push_back(compress(grid, x + half, y + half, half));   

    return new Node(children);
}

void printQuadTree(Node* node, int depth = 0) {
    if (!node) return;

    if (node->isLeaf) {
        cout << string(depth * 2, ' ') << node->val << endl;
    } else {
        cout << string(depth * 2, ' ') << "Internal Node" << endl;
        for (Node* child : node->children) {
            printQuadTree(child, depth + 1);
        }
    }
}

void deleteTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

int main() {
    vector<vector<int>> grid = {
        {2, 2, 3, 3},
        {2, 2, 3, 3},
        {4, 2, 5, 5},
        {2, 3, 5, 5}
    };

    Node* root = compress(grid, 0, 0, grid.size());
    cout << "Compressed QuadTree:\n";
    printQuadTree(root);
    deleteTree(root);

    return 0;
}
