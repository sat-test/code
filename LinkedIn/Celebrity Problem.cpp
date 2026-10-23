/*
Consider a party being organized by some people. A celebrity is a person who is known to all but does not know anyone at the party. 

A square matrix mat[][] of size n * n is used to represent people at the party such that if an element of row i and column j is set to 1 it means ith person knows jth person.
You need to return index of the celebrity in the party.
If the celebrity does not exist, return -1.
Note: Follow 0-based indexing.

Examples:

Input: mat[][] = [[1, 1, 0],
                 [0, 1, 0],
                 [0, 1, 1]]
Output: 1
Explanation: 0th and 2nd person both know 1st person and 1st person does not know anyone. Therefore, 1 is the celebrity person.
Input: mat[][] = [[1, 1], 
                 [1, 1]]
Output: -1
Explanation: Since both the people at the party know each other. Hence none of them is a celebrity person.
Input: mat[][] = [[1]]
Output: 0
*/

class Solution {
  public:
    int celebrity(vector<vector<int>>& mat) {
        int n = mat.size();
        vector<int> indegree(n, 0);
        vector<int> outdegree(n, 0);
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                outdegree[i] += mat[i][j];
                indegree[j] += mat[i][j];
            }
        }
        
        
        for(int i=0; i<n; i++) {
            if(indegree[i] == n && outdegree[i] == 1) {
                return i;
            }
        }
        
        return -1;
    }
};
