/*
Given the standard mapping from English letters to digits on a phone keypad:

(1 -> "",
2 -> a, b, c
3 -> d, e, f
4 -> g, h, i
5 -> j, k, l
6 -> m, n, o
7 -> p, q, r, s
8 -> t, u, v
9 -> w, x, y, z)

Write a program that outputs all words that can be formed from any n-digit phone number
from the list of given KNOWN_WORDS, considering the mapping mentioned above.

KNOWN_WORDS = ['careers', 'linkedin', 'hiring', 'interview', 'linkedgo']

phoneNumber: 2273377
Output: ['careers']

phoneNumber: 54653346
Output: ['linkedin', 'linkedgo']
*/

class Solution {
public:
    unordered_map<char, int> keypad;
    Solution() {
        for(int i=0; i<5; i++) {
            for(int j=0; j<3; j++) {
                char key = 'a' + 3*i + j;
                keypad[key] = i+2;
            }
        }
        for(char ch='p'; ch<='s'; ch++) keypad[ch] = 7; 
        for(char ch='t'; ch<='v'; ch++) keypad[ch] = 8; 
        for(char ch='w'; ch<='z'; ch++) keypad[ch] = 9; 
    }
    
    string getPhoneNumber(string word) {
        string number = "";
        for(char ch: word) {
            number += '0' + keypad[ch];
        }
        return number;
    }
    
    vector<string> findMatchingWords(string phoneNumber, vector<string>& knownWords) {
        vector<string> res;
        for(const string &word: knownWords) {
            if (word.size() != phoneNumber.size()) {
                continue;
            }
            string number = getPhoneNumber(word);
            if(number == phoneNumber) {
                res.push_back(word);
            }
        }

        return res;
    }
};

int main() {
    Solution s;
    vector<string> knownWords = {"careers", "linkedin", "hiring", "interview", "linkedgo"};
    string phoneNumber1 = "2273377";
    
    vector<string> res = s.findMatchingWords(phoneNumber1, knownWords);
    for(int i=0; i<res.size(); i++) {
        cout<<res[i]<<"\n";
    }
    
    string phoneNumber2 = "54653346";
    res = s.findMatchingWords(phoneNumber2, knownWords);
    for(int i=0; i<res.size(); i++) {
        cout<<res[i]<<"\n";
    }
}
