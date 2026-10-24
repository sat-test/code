/*
 String Replace Without Using Built-in Functions
Implement a function that will take three Strings as arguments and return the first string
with all instances of the second string replaced by the third string.

Do not use any of the standard regexp functions or string replace functions.

Example:
replace("AFoxRunsInTheField", "Fox", "Cat") => "ACatRunsInTheField"
*/

class Solution {
public:
    vector<int> createLPS(const string& str) {
        int n = str.size();
        vector<int> lps(n, 0);

        int i = 0, j = 1;

        while (j < n) {
            if (str[i] == str[j]) {
                lps[j] = ++i;
                ++j;
            } else if (i != 0) {
                i = lps[i - 1];
            } else {
                lps[j] = 0;
                ++j;
            }
        }

        return lps;
    }

    string replaceAll(string s, string searchWord, string replaceWord) {
        int n = s.size();
        int m = searchWord.size();

        if (m == 0) return s;

        vector<int> lps = createLPS(searchWord);
        string res;

        int i = 0, j = 0, lastEnd = 0;

        while (i < n) {
            if (s[i] == searchWord[j]) {
                ++i;
                ++j;
            } else if (j != 0) {
                j = lps[j - 1];
            } else {
                ++i;
            }

            if (j == m) {
                int start = i - m;

                res.append(s.begin() + lastEnd, s.begin() + start);
                res += replaceWord;

                lastEnd = i;
                j = 0;
            }
        }

        res.append(s.begin() + lastEnd, s.end());
        return res;
    }
};

int main() {
    Solution sol;

    struct TestCase {
        string s;
        string searchWord;
        string replaceWord;
        string expected;
    };

    vector<TestCase> tests = {
        {"AFoxRunsInTheField", "Fox", "Cat", "ACatRunsInTheField"},
        {"ababab", "ab", "xy", "xyxyxy"},
        {"aaaa", "aa", "b", "bb"},
        {"hello", "xyz", "abc", "hello"},
        {"catcat", "cat", "", ""},
        {"abcabc", "abc", "x", "xx"},
        {"aaaaa", "aa", "xyz", "xyzxyza"},
        {"abc", "abc", "xyz", "xyz"},
        {"abc", "a", "long", "longbc"},
        {"mississippi", "issi", "X", "mXssippi"},
        {"abababab", "abab", "z", "zz"},
        {"aaaa", "b", "x", "aaaa"},
        {"abcabcabc", "abc", "abc", "abcabcabc"},
        {"aabaaab", "aaab", "X", "aabX"}
    };

    int passed = 0;

    for (int i = 0; i < tests.size(); ++i) {
        string actual = sol.replaceAll(
            tests[i].s,
            tests[i].searchWord,
            tests[i].replaceWord
        );

        bool ok = (actual == tests[i].expected);

        cout << "Test " << i + 1 << ": "
             << (ok ? "PASS" : "FAIL") << '\n';

        if (!ok) {
            cout << "  Expected: \"" << tests[i].expected << "\"\n";
            cout << "  Actual:   \"" << actual << "\"\n";
        }

        passed += ok;
    }

    cout << "\nPassed: " << passed
         << "/" << tests.size() << '\n';

    return 0;
}
