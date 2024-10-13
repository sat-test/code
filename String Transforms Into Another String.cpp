/*
https://leetcode.com/problems/string-transforms-into-another-string/description/
https://leetcode.ca/2019-01-26-1153-String-Transforms-Into-Another-String/

Given two strings str1 and str2 of the same length, determine whether you can transform str1 into str2 by doing zero or more conversions.

In one conversion you can convert all occurrences of one character in str1 to any other lowercase English character.

Return true if and only if you can transform str1 into str2.
*/

int solve(string str1, string str2) {
    
    if(str1.size() != str2.size())  return false;
    if(str1 == str2) return true;
    
    unordered_set<char> s;
    for(auto ch : str2) {
        s.insert(ch);
    }
    if(s.size() == 26) {
        return false;
    }
    
    vector<int> A(26, 0);
    for(int i=0; i<str2.size(); i++) {
        int a = str1[i] - 'a';
        int b = str2[i] - 'a';
        if(A[a] == 0) {
            A[a] = b+1;
        } else if(A[a] != b+1) {
            return false;
        }
    }
    return true;
}


int main() {
    string str1 = "leetcode";
    string str2 = "codeleet";
    bool res = solve(str1, str2);
    cout<<res<<'\n';
}
