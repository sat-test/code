/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 1) {
            return strs[0];
        }
        string res = "";
        int j = 0;
        while(j < strs[0].size()) {
            char ch = strs[0][j];
            for(int i=1; i<strs.size(); i++) {
                if(j >= strs[i].size() || ch != strs[i][j]) {
                    return res;
                }
            }
            res += ch;
            ++j;
        }
        return res;
    }
};
