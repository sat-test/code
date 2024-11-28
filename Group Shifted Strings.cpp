/*
249. Group Shifted Strings
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:

"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

Example:

Input: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"],
Output:
[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
https://leetcode.ca/all/249.html
https://leetcode.com/problems/group-shifted-strings/description/
*/



#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Function to calculate the "shifting sequence" key for a string
string calculateKey(const string &str) {
    string key = "#"; // Start with a delimiter for uniqueness
    int n = str.size();
    for (int i = 1; i < n; i++) {
        int diff = (str[i] - str[i - 1] + 26) % 26; // Ensure non-negative modulo
        key += to_string(diff) + "#";              // Append diff with a separator
    }
    return key;
}

// Function to group strings by shifting sequence
vector<vector<string>> solve(vector<string> vec) {
    unordered_map<string, vector<string>> m; // Key: Shifting sequence, Value: Group of strings

    // Group strings by their keys
    for (const string &s : vec) {
        string key = calculateKey(s);
        m[key].push_back(s);
    }

    // Convert map to result vector
    vector<vector<string>> res;
    for (const auto &it : m) {
        res.push_back(it.second);
    }
    return res;
}

// Driver function
int main() {
    vector<string> input = {"abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"};
    vector<vector<string>> result = solve(input);

    // Print the grouped strings
    for (const auto &group : result) {
        cout << "[";
        for (const auto &str : group) {
            cout << str << " ";
        }
        cout << "]\n";
    }

    return 0;
}
