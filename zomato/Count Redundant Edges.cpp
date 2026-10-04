/*
You are given a list of n people labeled 0 to n-1. Some of them are directly friends with each other, represented as pairs in friendships. A friend circle is a group of people who are directly or indirectly friends.

Example:

n = 5  
friendships = [[0, 1], [2, 3], [3, 4]]  

Output: 2  
Explanation: {0,1}, {2,3,4}  
I explained the typical graph traversal approach (DFS/BFS) for counting connected components. He then asked for time and space complexity analysis.

He asked a follow-up question before I started coding.

Follow-up Question
Count the redundant edges (connections that can be removed without affecting the number of friend circles).
*/

class DSU{
private:
    vector<int> parent;
    vector<int> rank;
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for(int i=0; i<n; i++)  parent[i] = i;
    }
    
    int find(int x) {
        if(parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    
    bool unite(int u, int v) {
        int parentU = find(u);
        int parentV = find(v);
        
        if(parentU == parentV) {
            return false;
        }
        
        if(rank[parentU] < rank[parentV]) {
            parent[parentU] = parentV;
        } else if(rank[parentU] > rank[parentV]) {
            parent[parentV] = parentU;
        } else {
            parent[parentV] = parentU;
            rank[parentU]++;
        }
        
        return true;
    }
};


class Solution {
public:
    int countRedundantEdges(vector<vector<int>> friends, int n) {
        DSU dsu(n);
        
        int reduntantEdges = 0;
        for(auto &edge: friends) {
            int u = edge[0];
            int v = edge[1];
            
            if(!dsu.unite(u, v)) {
                reduntantEdges++;
            }
        }
        return reduntantEdges;
    }
};

int main() {
    Solution s;
    vector<vector<int>> friends = {{0, 1}, {2, 3}, {3, 4}, {4, 2}, {1, 2}, {1, 3}};
    int n = 5;
    int reduntantEdges = s.countRedundantEdges(friends, n);
    cout<<reduntantEdges<<"\n";
}
