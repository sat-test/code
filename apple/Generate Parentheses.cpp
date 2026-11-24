/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
*/

class Solution {
private:
    void solve(vector<string> &res, string str, int l, int r) {
        if(l == 0 && r == 0) {
            res.push_back(str);
            return;
        }
        if(l > 0) {
            solve(res, str + '(', l-1, r);
        }
        if(r > l) {
            solve(res, str + ')', l, r-1);
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        solve(res, "", n, n);
        return res;
    }
};
