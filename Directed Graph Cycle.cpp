class Solution {
  private:
    bool isCycleDetected(vector<vector<int>> &adj, vector<int> &visit, int curr) {
        visit[curr] = 1;
        for(auto a: adj[curr]) {
            if((visit[a] == 1) || (visit[a] == 0 && isCycleDetected(adj, visit, a))) {
                return true;
            }
        }
        visit[curr] = 2;
        return false;
    }
  public:
    bool isCyclic(int V, vector<vector<int>> &edges) {
        vector<vector<int>> adj(V);
        for(auto edge: edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
        }
        
        vector<int> visit(V, false);
        for(int i=0; i<V; i++) {
            if(visit[i] == 0 && isCycleDetected(adj, visit, i)) {
                return true;
            }
        }
        
        return false;
    }
};
