/*
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Example 1:
Input: haystack = "sadbutsad", needle = "sad"
Output: 0
Explanation: "sad" occurs at index 0 and 6.
The first occurrence is at index 0, so we return 0.

Example 2:
Input: haystack = "leetcode", needle = "leeto"
Output: -1
Explanation: "leeto" did not occur in "leetcode", so we return -1.

*/

class Solution {
public:
    vector<int> createLPS(string str) {
        int n = str.size();
        int i = 0, j = 1;
        vector<int> lps(n, 0);
        while(i < n && j < n) {
            if(str[i] == str[j]) {
                ++i;
                lps[j] = i;
                ++j;
            } else {
                if(i != 0) {
                    i = lps[i-1];
                } else {
                    lps[j] = 0;
                    ++j;
                }
            }
        }
        return lps;
    }

    int kmp(string str, string word) {
        int n = str.size(), m = word.size();
        vector<int> lps = createLPS(word);
        int i = 0, j = 0;
        while(i < n && j < m) {
            if(str[i] == word[j]) {
                ++i;
                ++j;
            } else {
                if(j != 0) {
                    j = lps[j-1];
                } else {
                    j = 0;
                    ++i;
                }
            }

            if(j == m) {
                return i-j;
            }
        }
        return -1;
    }

    int strStr(string haystack, string needle) {
        return kmp(haystack, needle);
    }
};
