/*
A valid IP address consists of exactly four integers separated by single dots. Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the valid IP addresses in any order.

Example 1:

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]
Example 2:

Input: s = "0000"
Output: ["0.0.0.0"]
Example 3:

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
*/

class Solution {
public:
    void traverse(string s, int pos, int dot, string curr, vector<string> &res) {
        if(dot == 4 && pos == s.size()) {
            res.push_back(curr.substr(0, curr.size()-1));
            return;
        } else if(dot == 4 && pos != s.size()) {
            return;
        }

        traverse(s, pos+1, dot+1, curr + s[pos] + ".", res);

        if(pos+1 < s.size() && s[pos] != '0') {
            traverse(s, pos+2, dot+1, curr + s[pos] + s[pos+1] + ".", res);
        }

        if(pos+2 < s.size()) {
            string temp = s.substr(pos, 3);
            if(temp <= "255" && temp[0] != '0') {
                traverse(s, pos+3, dot+1, curr + s[pos] + s[pos+1] + s[pos+2] + ".", res);
            }
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        traverse(s, 0, 0, "", res);
        return res;
    }
};
