/*
Problem: Minimum Latency Between Services
Problem Statement

You are given a network of N services, numbered from 1 to N, connected through directed communication links.

Each connection is represented by a triplet [u, v, w], where:

u is the source service.

v is the destination service.

w is the latency (in milliseconds) for communication from service u to service v.

You are also given Q queries. Each query [X, Y] asks you to find the minimum total latency required to travel from service X to service Y.

If there is no path between the two services, return -1.

Return the minimum latency for each query in the order they are given.

Example

Input:

N = 5

connections = [
    [1, 2, 200],
    [1, 3, 100],
    [3, 2, 50],
    [2, 4, 100],
    [3, 4, 300],
    [4, 5, 150]
]

queries = [
    [1, 4],
    [1, 5],
    [2, 5],
    [5, 1],
    [1, 3]
]
*/


// class Solution {
// public: 
//     int minimumLatencyForQuery(vector<vector<pair<int, int>>> &adj, int source, int destination, int N) {
//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
//         vector<int> dist(N, INT_MAX);
//         dist[source] = 0;
//         pq.push({0, source});
//         while(!pq.empty()) {
//             int lu = pq.top().first;
//             int u = pq.top().second;
//             pq.pop();
//             for(auto v: adj[u]) {
//                 int lv = lu + v.second;
//                 if(lv < dist[v.first]) {
//                     dist[v.first] = lv;
//                     pq.push({lv, v.first});
//                 }
//             }
//         }
//         return dist[destination] == INT_MAX ? -1 : dist[destination];
//     }
    
//     vector<int> minimumLatency(vector<vector<int>> &connections, int N, vector<vector<int>> &queries) {
//         vector<vector<pair<int, int>>> adj(N);
//         for(auto connection: connections) {
//             int u = connection[0];
//             int v = connection[1];
//             int w = connection[2];
//             adj[u].push_back({v, w});
//         }
//         vector<int> res;
//         for(auto query: queries) {
//             int mL = minimumLatencyForQuery(adj, query[0], query[1], N);
//             res.push_back(mL);
//         }
//         return res;
//     }
// };

// int main() {
//     Solution s;
    
//     int N = 5;
//     vector<vector<int>> connections = {
//         {1, 2, 200},
//         {1, 3, 100},
//         {3, 2, 50},
//         {2, 4, 100},
//         {3, 4, 300},
//         {4, 5, 150}
//     };
//     vector<vector<int>> queries = {
//         {1, 4},
//         {1, 5},
//         {2, 5},
//         {5, 1},
//         {1, 3}
//     };
//     vector<int> res = s.minimumLatency(connections, N+1, queries);
    
//     for(int i=0; i<res.size(); i++) {
//         cout<<res[i]<<"\n";
//     }
// }


#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    // Returns minimum distances from source to all nodes.
    vector<long long> dijkstra(
        vector<vector<pair<int, int>>>& adj,
        int source,
        int N
    ) {
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;

        vector<long long> dist(N, LLONG_MAX);

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            auto [lu, u] = pq.top();
            pq.pop();

            // Skip outdated heap entries.
            if (lu > dist[u]) {
                continue;
            }

            for (auto [v, w] : adj[u]) {
                long long lv = lu + w;

                if (lv < dist[v]) {
                    dist[v] = lv;
                    pq.push({lv, v});
                }
            }
        }

        return dist;
    }

public:
    vector<long long> minimumLatency(
        vector<vector<int>>& connections,
        int N,
        vector<vector<int>>& queries
    ) {
        vector<vector<pair<int, int>>> adj(N + 1);

        // Build adjacency list.
        for (auto& connection : connections) {
            int u = connection[0];
            int v = connection[1];
            int w = connection[2];

            adj[u].push_back({v, w});
        }

        // Cache shortest distances for each source.
        unordered_map<int, vector<long long>> cache;

        vector<long long> res;

        for (auto& query : queries) {
            int source = query[0];
            int destination = query[1];

            // Run Dijkstra only for a new source.
            if (cache.find(source) == cache.end()) {
                cache[source] = dijkstra(adj, source, N + 1);
            }

            long long latency = cache[source][destination];

            res.push_back(
                latency == LLONG_MAX ? -1 : latency
            );
        }

        return res;
    }
};

int main() {
    Solution s;

    int N = 5;

    vector<vector<int>> connections = {
        {1, 2, 200},
        {1, 3, 100},
        {3, 2, 50},
        {2, 4, 100},
        {3, 4, 300},
        {4, 5, 150}
    };

    vector<vector<int>> queries = {
        {1, 4},
        {1, 5},
        {2, 5},
        {5, 1},
        {1, 3},
        {1, 2},
        {1, 5}
    };

    vector<long long> res =
        s.minimumLatency(connections, N, queries);

    for (long long latency : res) {
        cout << latency << '\n';
    }
}
