/*
Given an integer n such that there is n × n Snakes and Ladders board with cells numbered from 1 to n*n and the following two arrays of even lengths:

lad[], where each pair (lad[2*i], lad[2*i + 1]) represents the start and end of a ladder.
sn[], where each pair (sn[2*i], sn[2*i + 1]) represents the start and end of a snake.
Find the minimum number of dice throws required to reach cell n*n starting from cell 1 with the following rules.

You have complete control over the outcome of each dice throw i.e., in a single move,  you can move forward by any number of cells from 1 to 6.  
If you land on the start cell of a snake or ladder, you must immediately move to its corresponding end cell.
If the end cell of a snake or ladder is also the start cell of another snake or ladder, do not follow the second snake or ladder. Only one snake or ladder is followed after each dice throw.
If it is impossible to reach cell n*n, return -1.
Examples:

Input: n = 6, lad[] = [3, 22, 5, 8, 11, 35, 20, 32], sn[] = [17, 4, 19, 7, 34, 1, 21, 9]
Output: 3
Explanation: For the 6 × 6 board, the minimum number of dice throws needed to reach cell 36 from cell 1 is 3.
One optimal path is:
Throw 4 to move from 1 to 5, then take the ladder to 8
Throw 3 to move from 8 to 11, then take the ladder to 35
Throw 1 to move from 35 to 36
So the destination is reached in 3 dice throws.
*/

class Solution {
  public:
    unordered_map<int, int> createJump(vector<int> jumpVec) {
        unordered_map<int, int> jump;
        for(int i=0; i<jumpVec.size(); i+=2) {
            int start = jumpVec[i];
            int end = jumpVec[i+1];
            jump[start] = end;
        }
        return jump;
    }
  
    int minThrows(int n, vector<int>& lad, vector<int>& sn) {
        int totalCells = n * n;
        unordered_map<int, int> ladder = createJump(lad);
        unordered_map<int, int> snake = createJump(sn);
        
        vector<int> dist(totalCells + 1, -1);
        queue<int> q;
        
        q.push(1);
        dist[1] = 0;
        
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            
            if(curr == totalCells) {
                return dist[curr];
            }
            
            for(int dice=1; dice<=6; dice++) {
                int next = curr + dice;
                
                if(next > totalCells) {
                    continue;
                }
                
                if(ladder.count(next)) {
                    next = ladder[next];
                } else if(snake.count(next)) {
                    next = snake[next];
                }
                
                if(dist[next] != -1) {
                    continue;
                }
                
                dist[next] = dist[curr] + 1;
                q.push(next);
            }
        }
        
        return -1;
    }
};
