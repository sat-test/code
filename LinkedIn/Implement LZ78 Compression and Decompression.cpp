/*
Implement the LZ78 compression algorithm, which compresses a string into a sequence of pairs, and its corresponding decompression algorithm, which reconstructs the original string from those pairs.

LZ78 builds a dictionary of phrases while processing the input. Each new phrase is formed by concatenating an existing dictionary phrase with one character.
Compression rules
1. Initially, the dictionary contains phrase 0, which represents the empty string "".
2. Process the input from left to right.
3. Find the longest prefix of the remaining input that is already in the dictionary.
4. Append the next character to that prefix to form a new phrase.
5. Output a pair (index, character), where index identifies the existing prefix in the dictionary.
6. Add the new phrase to the dictionary with the next available index.
7. If the input ends with a phrase already in the dictionary, output (index, '\0') to represent the final phrase with no additional character.
Function signatures
vector<pair<int, char>> compress(string s);

string decompress(vector<pair<int, char>> encoded);

Example 1
Input:
s = "aababababbaa"

Output of compression:
[(0, 'a'), (1, 'b'), (2, 'a'),
 (0, 'b'), (2, 'b'), (1, 'a')]

Explanation:

The dictionary is built as follows:
Index	Phrase	Created from
0	""	Initial empty phrase
1	"a"	(0, 'a')
2	"ab"	(1, 'b')
3	"aba"	(2, 'a')
4	"b"	(0, 'b')
5	"abb"	(2, 'b')
6	"aa"	(1, 'a')
*/

class Solution {
public:
    vector<pair<int, char>> compress(string s) {
        unordered_map<string, int> m;
        vector<pair<int, char>> res;
        m[""] = 0;
        int index = 0, i = 0, n = s.size();
        while(i < n) {
            string prevTemp = "";
            string temp = "";
            while(i < n) {
                temp += s[i];
                if(m.find(temp) == m.end()) {
                    res.push_back({m[prevTemp], s[i]});
                    m[temp] = ++index;
                    break;
                }
                prevTemp = temp;
                ++i;
            }
            ++i;
        }
        return res;
    }

    string decompress(vector<pair<int, char>> encoded) {
        unordered_map<int, string> m;
        m[0] = "";
        string res = "";
        int index = 0;

        for(auto p: encoded) {
            int code = p.first;
            char letter = p.second;
            string temp = m[code] + letter;
            m[++index] = temp;
            res += temp;
        }
        return res;
    }
};

int main() {
    Solution s;
    string str = "aababababbaa";
    vector<pair<int, char>> vec = s.compress(str);
    cout<<"Compress : "<<"\n";
    for(auto it: vec) {
        cout<<it.first<<" "<<it.second<<"\n";
    }
    cout<<"Decompress : "<<s.decompress(vec)<<"\n";
}
