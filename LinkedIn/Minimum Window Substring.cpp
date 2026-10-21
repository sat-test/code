/*
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 
*/
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> m;
        for(char ch: t) {
            ++m[ch];
        }

        vector<pair<char, int>> vec;
        for(int i=0; i<s.size(); i++) {
            if(m.find(s[i]) != m.end()) {
                vec.push_back({s[i], i});
            }
        }

        m.clear();
        for (char ch : t) {
            ++m[ch];
        }

        deque<int> dq;
        int maxi = INT_MAX;
        pair<int, int> range = {-1, -1};
        int missing = t.size();

        for(int i=0; i<vec.size(); i++) {
            char ch = vec[i].first;
            int index = vec[i].second;

            dq.push_back(index);
            if (m[ch] > 0) {
                --missing;
            }

            --m[ch];

            while(missing == 0) {
                int l = dq.front();
                int r = dq.back() - l + 1;

                if(r < maxi) {
                    maxi = r;
                    range = {l, dq.back()};
                }

                int prevIndex = dq.front();
                dq.pop_front();
                ++m[s[prevIndex]];
                
                if (m[s[prevIndex]] > 0) {
                    ++missing;
                }
            }
        }

        if(range.first == -1) {
            return "";
        }
        
        return s.substr(range.first, range.second - range.first + 1);
    }
};
