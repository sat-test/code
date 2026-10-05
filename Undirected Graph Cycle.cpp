class Solution {
  private: 
    bool isCycleDetected(vector<vector<int>> &adj, vector<bool> &visit, int curr, int prev) {
        visit[curr] = true;
        for(int i=0; i<adj[curr].size(); i++) {
            if(!visit[adj[curr][i]]) {
                if(isCycleDetected(adj, visit, adj[curr][i], curr)) {
                    return true;
                }
            } else if(adj[curr][i] != prev) {
                return true;
            }
        }
        return false;
    }
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<vector<int>> adj(V);
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> visit(V, false); 
        for(int i=0; i<V; i++) {
            if(!visit[i] && isCycleDetected(adj, visit, i, -1)) {
                return true;
            }
        }
        
        return false;
    }
};
