/*
You are given a list of n people labeled 0 to n-1. Some of them are directly friends with each other, represented as pairs in friendships. A friend circle is a group of people who are directly or indirectly friends.

Example:

n = 5  
friendships = [[0, 1], [2, 3], [3, 4]]  

Output: 2  
Explanation: {0,1}, {2,3,4}  
I explained the typical graph traversal approach (DFS/BFS) for counting connected components. He then asked for time and space complexity analysis.
*/

class Solution {
private: 
   void dfs(vector<vector<int>> &adj, int pos, vector<bool> &visit, vector<int> &circle) {
       visit[pos] = true;
       circle.push_back(pos);
       for(int i=0; i<adj[pos].size(); i++) {
           if(!visit[adj[pos][i]]) {
               dfs(adj, adj[pos][i], visit, circle);
           }
       }
   }
public:
    vector<vector<int>> findFriendCircle(vector<vector<int>> friends, int n) {
        vector<vector<int>> adj(n);
        
        for(auto frnd: friends) {
            adj[frnd[0]].push_back(frnd[1]);
            adj[frnd[1]].push_back(frnd[0]);
        }
        
        vector<bool> visit(n, false);
        vector<vector<int>> res;
        for(int i=0; i<n; i++) {
            if(!visit[i]) {
                vector<int> circle;
                dfs(adj, i, visit, circle);
                res.push_back(circle);
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<vector<int>> friends = {{0, 1}, {2, 3}, {3, 4}};
    int n = 5;
    vector<vector<int>> circles = s.findFriendCircle(friends, n);
    for(int i=0; i<circles.size(); i++) {
        for(int j=0; j<circles[i].size(); j++) {
            cout<<circles[i][j]<<" ";
        }
        cout<<"\n";
    }
}
