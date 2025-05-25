/*
261. Graph Valid Tree (https://leetcode.com/problems/graph-valid-tree/description/)
Given n nodes labeled from 0 to n-1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

Example 1:
Input: n = 5, and edges = [[0,1], [0,2], [0,3], [1,4]]
Output: true

Example 2:

Input: n = 5, and edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
Output: false


Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0,1] is the same as [1,0] and thus will not appear together in edges.
*/

class Solution {
public:
    vector<int> p;
    
    int find(int x) {
        if(p[x] != x) {
            p[x] = find(p[x]);
        }
        return p[x];
    }
    
    bool validTree(int n, vector<vector<int>> &edges) {
        p.resize(n);
        for(int i=0; i<n; i++) {
            p[i] = i;
        }
        for(auto edge : edges) {
            int a = edge[0], b = edge[1];
            int a1 = find(a), b1 = find(b);
            if(a1 == b1) {
                return false;
            }
            p[a1] = b1;
            --n;
        }
        return n == 1;
    }
};

int main() {
    Solution s;
    int n = 5;
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{1,3},{1,4}};
    cout<<s.validTree(n, edges)<<"\n";
    
    n = 5;
    edges = {{0,1},{0,2},{0,3},{1,4}};
    cout<<s.validTree(n, edges)<<"\n";
}
