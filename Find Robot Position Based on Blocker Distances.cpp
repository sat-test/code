/*
https://leetcode.com/discuss/post/6767457/uber-technical-interview-experience-l4-b-sok4/

Question
you have a grid with 3 type of elements O, X, E.
O denotes robot
X denotes blocker
E denotes empty space
grid is of size M x N.

you are also given an array of size 4 with [L, T, B, R] which represents the closest blocker at distance L from left of robot, distance T from Top of robot, distance B from bottom of robot, distance R from right of robot. boundary outside matrix is considered as blocker.

give the position of the robot which satisfies given criteria if there is one, else return [-1, -1]
closest blocker should absolutely exist at given position L, T, B, R. if it does not, it's not valid robot.

grid = [
    ['E', 'X', 'E', 'E'],
    ['O', 'E', 'X', 'E'],
    ['E', 'E', 'E', 'X'],
    ['X', 'E', 'E', 'E']
]
blockers = [1, 1, 1, 1]

*/

#include <iostream>
#include <vector>
using namespace std;

vector<int> findRobotPositionOptimized(vector<vector<char>>& grid, vector<int>& blockers) {
    int m = grid.size();
    int n = grid[0].size();
    int L = blockers[0], T = blockers[1], B = blockers[2], R = blockers[3];
    
    // Precompute distances to closest blockers for all positions
    vector<vector<int>> leftDist(m, vector<int>(n));
    vector<vector<int>> topDist(m, vector<int>(n));
    vector<vector<int>> bottomDist(m, vector<int>(n));
    vector<vector<int>> rightDist(m, vector<int>(n));
    
    // Calculate left distances
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0 || grid[i][j-1] == 'X') {
                leftDist[i][j] = 1;
            } else {
                leftDist[i][j] = leftDist[i][j-1] + 1;
            }
        }
    }
    
    // Calculate top distances
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            if (i == 0 || grid[i-1][j] == 'X') {
                topDist[i][j] = 1;
            } else {
                topDist[i][j] = topDist[i-1][j] + 1;
            }
        }
    }
    
    // Calculate right distances
    for (int i = 0; i < m; i++) {
        for (int j = n-1; j >= 0; j--) {
            if (j == n-1 || grid[i][j+1] == 'X') {
                rightDist[i][j] = 1;
            } else {
                rightDist[i][j] = rightDist[i][j+1] + 1;
            }
        }
    }
    
    // Calculate bottom distances
    for (int j = 0; j < n; j++) {
        for (int i = m-1; i >= 0; i--) {
            if (i == m-1 || grid[i+1][j] == 'X') {
                bottomDist[i][j] = 1;
            } else {
                bottomDist[i][j] = bottomDist[i+1][j] + 1;
            }
        }
    }
    
    // Find robot position that matches the criteria
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'O') {
                if (leftDist[i][j] == L && topDist[i][j] == T && 
                    bottomDist[i][j] == B && rightDist[i][j] == R) {
                    return {i, j};
                }
            }
        }
    }
    
    return {-1, -1};
}

void printGrid(vector<vector<char>>& grid) {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void testCase(int testNum, vector<vector<char>>& grid, vector<int>& blockers, string description) {
    cout << "=== Test Case " << testNum << ": " << description << " ===" << endl;
    cout << "Grid:" << endl;
    printGrid(grid);
    cout << "Blockers [L,T,B,R]: [" << blockers[0] << "," << blockers[1] << "," << blockers[2] << "," << blockers[3] << "]" << endl;
    
    vector<int> result = findRobotPositionOptimized(grid, blockers);
    cout << "Result: [" << result[0] << ", " << result[1] << "]" << endl;
    cout << endl;
}

int main() {
    // Test Case 1: Original example - Robot surrounded by blockers at distance 1
    vector<vector<char>> grid1 = {
        {'E', 'X', 'E', 'E'},
        {'O', 'E', 'X', 'E'},
        {'E', 'E', 'E', 'X'},
        {'X', 'E', 'E', 'E'}
    };
    vector<int> blockers1 = {1, 1, 1, 1};
    testCase(1, grid1, blockers1, "Robot with all blockers at distance 1");
    
    // Test Case 2: Robot at corner - boundaries act as blockers
    vector<vector<char>> grid2 = {
        {'O', 'E', 'E'},
        {'E', 'X', 'E'},
        {'E', 'E', 'E'}
    };
    vector<int> blockers2 = {1, 1, 3, 3}; // Left=boundary(1), Top=boundary(1), Bottom=3, Right=3
    testCase(2, grid2, blockers2, "Robot at top-left corner");
    
    // Test Case 3: Robot with varying distances
    vector<vector<char>> grid3 = {
        {'E', 'E', 'E', 'E', 'E'},
        {'X', 'E', 'O', 'E', 'X'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'X', 'E', 'E'}
    };
    vector<int> blockers3 = {2, 1, 2, 2}; // Left=2, Top=1(boundary), Bottom=2, Right=2
    testCase(3, grid3, blockers3, "Robot with mixed distances");
    
    // Test Case 4: Multiple robots - should find the correct one
    vector<vector<char>> grid4 = {
        {'O', 'X', 'E', 'E'},
        {'E', 'E', 'E', 'E'},
        {'E', 'E', 'O', 'X'},
        {'E', 'E', 'E', 'E'}
    };
    vector<int> blockers4 = {2, 2, 2, 1}; // Should match robot at (2,2)
    testCase(4, grid4, blockers4, "Multiple robots - find correct one");
    
    // Test Case 5: No valid robot
    vector<vector<char>> grid5 = {
        {'O', 'X', 'E'},
        {'E', 'E', 'E'},
        {'E', 'E', 'X'}
    };
    vector<int> blockers5 = {3, 3, 3, 3}; // Impossible distances
    testCase(5, grid5, blockers5, "No valid robot (should return [-1,-1])");
    
    // Test Case 6: Robot in center with symmetric blockers
    vector<vector<char>> grid6 = {
        {'E', 'E', 'X', 'E', 'E'},
        {'E', 'E', 'E', 'E', 'E'},
        {'X', 'E', 'O', 'E', 'X'},
        {'E', 'E', 'E', 'E', 'E'},
        {'E', 'E', 'X', 'E', 'E'}
    };
    vector<int> blockers6 = {2, 2, 2, 2}; // All directions have blockers at distance 2
    testCase(6, grid6, blockers6, "Robot in center with symmetric blockers");
    
    // Test Case 7: Edge case - Single cell grid
    vector<vector<char>> grid7 = {
        {'O'}
    };
    vector<int> blockers7 = {1, 1, 1, 1}; // All boundaries at distance 1
    testCase(7, grid7, blockers7, "Single cell grid");
    
    // Test Case 8: Robot relying on boundaries
    vector<vector<char>> grid8 = {
        {'E', 'E', 'E', 'O'},
        {'E', 'E', 'E', 'E'},
        {'E', 'E', 'E', 'E'}
    };
    vector<int> blockers8 = {4, 1, 3, 1}; // Left=4, Top=1, Bottom=3, Right=1(boundary)
    testCase(8, grid8, blockers8, "Robot relying on boundaries");
    
    return 0;
}
