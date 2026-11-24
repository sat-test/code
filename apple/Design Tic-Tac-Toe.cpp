/*
Problem statement
Ninja has to design a 2 players game Tic-Tac-Toe played on an ‘N’ * ‘N’ grid.

Ninja has to assume the following rules while playing the game:

This game is played between two people (Player 1 and Player 2). Player 1 chooses ‘X' and Player 2 chooses ‘O’ to mark their cells. A move is guaranteed to be valid and is placed on an empty block.

A player who successfully places 'N' of their marks in a horizontal, vertical, or diagonal row wins the game. Once a winning condition is reached, no more moves are allowed.
As Ninja is busy planning his strategy, he asks you for help. Your task is to complete the function ‘move(row, col, player)’ where ‘row’ and ‘col’ represent the current row and column of the grid ‘player’ P (either 1 or 2) chooses to place his sign.

The function must return an integer which is either 0, 1, and 2 representing:

0: No one wins.
1: Player 1 wins.
2: Player 2 wins.
Example:

Let us assume if ‘N’ = 3 and player 1 places ‘X’ and player 2 places ‘O’ on the board.
*/

class Solution {
private:
	vector<vector<int>> vec;
	bool checkWinner(int row, int col, int player) {
		int i = 0, j = 0, n = vec.size();
		while(i < n && j < n && vec[i][j] == player) {
			++i, ++j;
		}
		if(i == n && j == n) {
			return true;
		}
		
		i = 0, j = n - 1;
        while(i < n && j >= 0 && vec[i][j] == player) {
            ++i, --j;
        }
        if(i == n) {
            return true;
        }

		i = 0;
		while(i < n && vec[i][col] == player) {
			++i;
		}
		if(i == n) {
			return true;
		}
		
		j = 0;
		while(j < n && vec[row][j] == player) {
			++j;
		}
		if(j == n) {
			return true;
		}
		return false;
	}
public:
	Solution(int n) {
		vec = vector<vector<int>>(n, vector<int>(n, 0));
	}

	int move(int row, int col, int player) {
		vec[row][col] = player;
		if(checkWinner(row, col, player)) {
			return player;
		}
		return 0;
	}
};
