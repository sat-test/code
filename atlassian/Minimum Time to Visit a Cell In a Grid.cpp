/*
You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].

You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.

Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.

Example 1:



Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One of the paths that we can take is the following:
- at t = 0, we are on the cell (0,0).
- at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
- at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
- at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
- at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
- at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
- at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
- at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
The final time is 7. It can be shown that it is the minimum time possible.
Example 2:

Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
Output: -1
Explanation: There is no path from the top left to the bottom-right cell.

*/

class Solution {
public:
    int X[4] = {0, 0, -1, 1};
    int Y[4] = {-1, 1, 0, 0};

    int isValid(int n, int m, int row, int col, int prevDist, vector<vector<int>> &dist, vector<vector<int>> &grid) {
        if(row >= 0 && row < n && col >= 0 && col < m) {
            int d = prevDist+1;
            if(d < grid[row][col]) {
                d = grid[row][col] + (grid[row][col] - d) % 2;
            }
            if((dist[row][col] == -1) || (dist[row][col] > d)) {
                dist[row][col] = d;
                return true;
            }
        }
        return false;
    }
    int minimumTime(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        if ((n > 1 && grid[1][0] > 1) && (m > 1 && grid[0][1] > 1)) {
            return -1;
        }

        vector<vector<int>> dist(n, vector<int>(m, -1));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

        pq.push({0, 0, 0});
        dist[0][0] = 0;

        while(!pq.empty()) {
            int d = pq.top()[0];
            int row = pq.top()[1];
            int col = pq.top()[2];
            pq.pop();

            if (d != dist[row][col]) {
                continue;
            }

            if(row == n-1 && col == m-1) {
                return dist[row][col];
            }
            
            for(int i=0; i<4; i++) {
                int newRow = row + X[i];
                int newCol = col + Y[i];
                if(isValid(n, m, newRow, newCol, dist[row][col], dist, grid)) {
                    pq.push({dist[newRow][newCol], newRow, newCol});
                }
            }
        }
        
        return -1;
    }
};
