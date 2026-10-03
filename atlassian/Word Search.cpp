/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
 

Follow up: Could you use search pruning to make your solution faster with a larger board?
*/

class Solution {
public:
    int X[4] = {0, 0, -1, 1};
    int Y[4] = {-1, 1, 0, 0};
    
    bool isValid(vector<vector<char>> &board, vector<vector<bool>> &visit, int x, int y, int pos, string word) {
        if(pos == word.size()) {
            return true;
        }

        if(x < 0 || y < 0 || x >= board.size() || y >= board[0].size() || visit[x][y] || board[x][y] != word[pos]) {
            return false;
        }

        visit[x][y] = true;
        for(int i=0; i<4; i++) {
            if(isValid(board, visit, x+X[i], y+Y[i], pos+1, word)) {
                return true;
            }
        }
        
        return visit[x][y] = false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> visit(n, vector<bool>(m, false));
        for(int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(board[i][j] == word[0] && isValid(board, visit, i, j, 0, word)) {
                    return true;
                }
            }
        }
        return false;
    }
};
