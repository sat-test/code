/*
Shortest Cycle in a Graph

There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1. The edges in the graph are represented by a given 2D integer array edges, where edges[i] = [ui, vi] denotes an edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

Return the length of the shortest cycle in the graph. If no cycle exists, return -1.

A cycle is a path that starts and ends at the same node, and each edge in the path is used only once.

Example 1:

Input: n = 7, edges = [[0,1],[1,2],[2,0],[3,4],[4,5],[5,6],[6,3]]
Output: 3
Explanation: The cycle with the smallest length is : 0 -> 1 -> 2 -> 0 

Example 2:

Input: n = 4, edges = [[0,1],[0,2]]
Output: -1
Explanation: There are no cycles in this graph.

*/

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        int res = INT_MAX;
        vector<vector<int>> adj(n);
        for(auto edge: edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        for(int src=0; src<n; src++) {
            vector<int> dist(n, -1);
            vector<int> parent(n, -1);
            queue<int> q;
            dist[src] = 0;
            q.push(src);
            
            while(!q.empty()) {
                int node = q.front();
                q.pop();

                for(auto a: adj[node]) {
                    if(dist[a] == -1) {
                        dist[a] = dist[node] + 1;
                        parent[a] = node;
                        q.push(a);
                    } else if(parent[node] != a) {
                        res = min(res, dist[node] + dist[a] + 1);
                    }
                }
            }
        }

        return res == INT_MAX ? -1 : res;
    }
};
