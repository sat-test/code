class Solution {
private:
    unordered_map<char, int> keypad;
    unordered_map<string, unordered_set<string>> m;
    
    string getPhoneNumber(string word) {
        string number = "";
        for(char ch: word) {
            number += '0' + keypad[ch];
        }
        return number;
    }
public:
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
    
    void addWord(string word) {
        string number = getPhoneNumber(word);
        m[number].insert(word);
    }

    void removeWord(string word) {
        string number = getPhoneNumber(word);
        if((m.find(number) != m.end()) && m[number].find(word) != m[number].end()) {
            m[number].erase(word);
            if(m[number].size() == 0) {
                m.erase(number);
            }
        }
    }

    vector<string> findMatchingWords(string phoneNumber) {
        vector<string> res;
        if(m.find(phoneNumber) == m.end()) {
            return res;
        }
        for(auto it: m[phoneNumber]) {
            res.push_back(it);
        }
        return res;
    }
};

void print(const vector<string>& words) {
    cout << "[";
    for (int i = 0; i < words.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "\"" << words[i] << "\"";
    }
    cout << "]\n";
}

int main() {
    Solution s;

    // Test 1: Empty word and empty phone number
    s.addWord("");
    s.removeWord("");
    cout << "Test 1: ";
    print(s.findMatchingWords(""));

    // Test 2: Add known words and verify matches
    s.addWord("careers");
    s.addWord("linkedin");
    s.addWord("hiring");
    s.addWord("interview");
    s.addWord("linkedgo");

    cout << "Test 2: ";
    print(s.findMatchingWords("2273377"));  // careers

    cout << "Test 3: ";
    print(s.findMatchingWords("54653346")); // linkedin, linkedgo

    // Test 4: No matching word
    cout << "Test 4: ";
    print(s.findMatchingWords("4664"));     // empty

    // Test 5: Duplicate addition
    s.addWord("careers");
    cout << "Test 5: ";
    print(s.findMatchingWords("2273377"));  // careers only once

    // Test 6: Remove existing word
    s.removeWord("careers");
    cout << "Test 6: ";
    print(s.findMatchingWords("2273377"));  // empty

    // Test 7: Remove one of multiple matches
    s.removeWord("linkedin");
    cout << "Test 7: ";
    print(s.findMatchingWords("54653346")); // linkedgo

    // Test 8: Remove nonexistent word
    s.removeWord("unknown");
    cout << "Test 8: ";
    print(s.findMatchingWords("54653346")); // linkedgo

    // Test 9: Add a word after deletion
    s.addWord("careers");
    cout << "Test 9: ";
    print(s.findMatchingWords("2273377"));  // careers

    // Test 10: Digit 1 has no letter mapping
    cout << "Test 10: ";
    print(s.findMatchingWords("123"));      // empty

    // Test 11: Remove the same word twice
    s.removeWord("careers");
    s.removeWord("careers");
    cout << "Test 11: ";
    print(s.findMatchingWords("2273377"));  // empty

    return 0;
}
