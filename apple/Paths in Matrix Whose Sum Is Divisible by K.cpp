/*
You are given a 0-indexed m x n integer matrix grid and an integer k. You are currently at position (0, 0) and you want to reach position (m - 1, n - 1) moving only down or right.

Return the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 109 + 7.

Example 1:

Input: grid = [[5,2,4],[3,0,5],[0,7,2]], k = 3
Output: 2
Explanation: There are two paths where the sum of the elements on the path is divisible by k.
The first path highlighted in red has a sum of 5 + 2 + 4 + 5 + 2 = 18 which is divisible by 3.
The second path highlighted in blue has a sum of 5 + 3 + 0 + 5 + 2 = 15 which is divisible by 3.
Example 2:

Input: grid = [[0,0]], k = 5
Output: 1
Explanation: The path highlighted in red has a sum of 0 + 0 = 0 which is divisible by 5.
Example 3:

Input: grid = [[7,3,4,9],[2,3,6,2],[2,3,7,0]], k = 1
Output: 10
Explanation: Every integer is divisible by 1 so the sum of the elements on every possible path is divisible by k.
*/

class Solution {
private: 
    const int MOD = 1e9+7;
    int traverse(int i, int j, int sum, int k, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp) {
        int res = 0;
        if(i >= grid.size() || j >= grid[i].size()) return 0;
        if(i == grid.size()-1 && j == grid[0].size()-1) {
            if((sum + grid[i][j]) % k == 0) {
                return 1;
            }
            return 0;
        }
        if(dp[i][j][sum] != -1) {
            return dp[i][j][sum];
        }
        res = (res + traverse(i+1, j, (sum + grid[i][j])%k, k, grid, dp)) % MOD;
        res = (res + traverse(i, j+1, (sum + grid[i][j])%k, k, grid, dp)) % MOD;
        return dp[i][j][sum] = res;
    }
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, -1)));
        return traverse(0, 0, 0, k, grid, dp);
    }
};
