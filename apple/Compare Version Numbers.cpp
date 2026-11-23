/*
Given two version strings, version1 and version2, compare them. A version string consists of revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading zeros.
To compare version strings, compare their revision values in left-to-right order. If one of the version strings has fewer revisions, treat the missing revision values as 0.

Return the following:
If version1 < version2, return -1.
If version1 > version2, return 1.
Otherwise, return 0.
 

Example 1:
Input: version1 = "1.2", version2 = "1.10"
Output: -1

Explanation:
version1's second revision is "2" and version2's second revision is "10": 2 < 10, so version1 < version2.

Example 2:
Input: version1 = "1.01", version2 = "1.001"
Output: 0

Explanation:
Ignoring leading zeroes, both "01" and "001" represent the same integer "1".

Example 3:
Input: version1 = "1.0", version2 = "1.0.0.0"

Output: 0
Explanation:
version1 has less revisions, which means every missing revision are treated as "0".
*/

class Solution {
private:
    vector<string> buildVec(string version) {
        string str = "";
        int i = 0, n = version.size();
        vector<string> vec;
        while(i < n) {
            if(version[i] == '.') {
                vec.push_back(str);
                str = "";
            } else {
                str += version[i];
            }
            ++i;
        }
        vec.push_back(str);
        return vec;
    }
    int compare(string str1, string str2) {
        int i = 0, j = 0, m = str1.size(), n = str2.size();
        while(i < m && str1[i] == '0')  ++i;
        while(j < n && str2[j] == '0')  ++j;
        
        if((m-i) > (n-j))   return 1;
        if((m-i) < (n-j))  return -1;
        
        while(i < m && j < n) {
            if(str1[i] > str2[j])   return 1;
            if(str1[i] < str2[j])   return -1;
            ++i;
            ++j;
        }

        return 0;
    }
    bool isZero(string str) {
        for(int i=0; i<str.size(); i++) {
            if(str[i] != '0')   return false;
        }
        return true;
    }
public:
    int compareVersion(string version1, string version2) {
        vector<string> vec1 = buildVec(version1);
        vector<string> vec2 = buildVec(version2);

        int i = 0, j = 0, m = vec1.size(), n = vec2.size();
        while(i < m && j < n) {
            int val = compare(vec1[i], vec2[j]);
            if(val != 0)    return val;
            ++i;
            ++j;
        }
        while(i < m) {
            if(!isZero(vec1[i])) return 1;
            ++i;
        }
        while(j < n) {
            if(!isZero(vec2[j])) return -1;
            ++j;
        }
        return 0;
    }
};
