/*
Problem Statement
LinkedIn connects users through professional connections. Given a network of users and their connections, determine the connection distance between two users.

The connection distance is the minimum number of connections required to travel from one user to another.

A connection between two users is bidirectional.

For example, if Bob is connected to Alice, and Alice is connected to Frank, then the connection distance between Bob and Frank is 2, assuming no shorter path exists.

Implement the getConnectionDistance function to return the shortest connection distance between two users.

If no connection path exists between the two users, return -1.

Parameters
- n: Number of users, identified by integers from 0 to n - 1.
- connections: A list of bidirectional connections, where connections[i] = [u, v] means user u is connected to user v.
- source: The starting user's ID.
- target: The destination user's ID.
Examples
Example 1
Input
n = 4
connections = {{0, 1}, {1, 2}, {2, 3}}
source = 0
target = 3

Output
3

Input:
n = 5
connections = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}}
source = 0
target = 3

Output:
2

*/

class Solution {
private:
    int inf = 100005;
public: 
//     int getConnectionDistance(int n, vector<vector<int>>& connections, int source, int target){
//         vector<vector<int>> adj(n);
//         for(auto connection: connections) {
//             adj[connection[0]].push_back(connection[1]);
//             adj[connection[1]].push_back(connection[0]);
//         }
//         vector<int> dist(n, inf);
//         queue<int> q;
        
//         pq.push({0, source});
//         dist[source] = 0;
        
//         while(!pq.empty()) {
//             int du = pq.top().first;
//             int u = pq.top().second;
//             pq.pop();
//             if(u == target) {
//                 return du;
//             }
//             for(auto v: adj[u]) {
//                 int dv = du + 1;
//                 if(dist[v] > dv) {
//                     dist[v] = dv;
//                     pq.push({dv, v});
//                 }
//             }
//         }
//         return -1;
//     }

    int getConnectionDistance(int n, vector<vector<int>>& connections, int source, int target) {
        vector<vector<int>> adj(n);

        for (const auto& connection : connections) {
            adj[connection[0]].push_back(connection[1]);
            adj[connection[1]].push_back(connection[0]);
        }

        vector<int> dist(n, -1);
        queue<int> q;

        q.push(source);
        dist[source] = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == target) {
                return dist[u];
            }

            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    
    int n = 4;
    vector<vector<int>> connections = {{0, 1}, {1, 2}, {2, 3}};
    int source = 0;
    int target = 3;
    
    cout<<s.getConnectionDistance(n, connections, source, target)<<"\n";
    
    n = 5;
    connections = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {3, 4}};
    source = 0;
    target = 3;
    
    cout<<s.getConnectionDistance(n, connections, source, target)<<"\n";
}
