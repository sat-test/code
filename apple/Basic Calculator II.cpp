/*
Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
*/

class Solution {
public:
    int calculate(string s) {
        stack<int> stk;
        char sign = '+';
        int num = 0, res = 0;
        for(int i=0; i<s.size(); i++) {
            char ch = s[i];
            if(isdigit(ch)) {
                num = num*10 + (ch - '0');
            }
            if((!isdigit(ch) && ch != ' ') || (i == s.size()-1)) {
                if(sign == '+') {
                    stk.push(num);
                } else if(sign == '-') {
                    stk.push(-num);
                } else if(sign == '*') {
                    int val = stk.top() * num;
                    stk.pop();
                    stk.push(val);
                } else if(sign == '/') {
                    int val = stk.top() / num;
                    stk.pop();
                    stk.push(val);
                }
                sign = ch;
                num = 0;
            }
        }
        
        while(!stk.empty()) {
            res += stk.top();
            stk.pop();
        }

        return res;
    }
};
