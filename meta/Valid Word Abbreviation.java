/*
A string can be abbreviated by replacing any number of non-adjacent, non-empty substrings with their lengths. The lengths should not have leading zeros.

For example, a string such as "substitution" could be abbreviated as (but not limited to):

"s10n" ("s ubstitutio n")
"sub4u4" ("sub stit u tion")
"12" ("substitution")
"su3i1u2on" ("su bst i t u ti on")
"substitution" (no substrings replaced)
The following are not valid abbreviations:

"s55n" ("s ubsti tutio n", the replaced substrings are adjacent)
"s010n" (has leading zeros)
"s0ubstitution" (replaces an empty substring)
Given a string word and an abbreviation abbr, return whether the string matches the given abbreviation.

A substring is a contiguous non-empty sequence of characters within a string.

Example 1:
Input: word = "internationalization", abbr = "i12iz4n"
Output: true
Explanation: The word "internationalization" can be abbreviated as "i12iz4n" ("i nternational iz atio n").

Example 2:
Input: word = "apple", abbr = "a2e"
Output: false
Explanation: The word "apple" cannot be abbreviated as "a2e".
*/



public class Main {
    public static boolean validWordAbbreviation(String word, String abbr) {
        int i = 0, j = 0, n = word.length(), m = abbr.length(), x = 0;
        while(i < n && j < m) {
            char ch = abbr.charAt(j);
            if(Character.isDigit(ch)) {
                if(ch == '0' && x == 0) {
                    return false;
                }
                x = x * 10 + (ch - '0');
            } else {
                i += x;
                x = 0;
                if(i >= n || word.charAt(i) != ch) {
                    return false;
                }
                ++i;
            }
            ++j;
        }
        
        return (((i+x) == n) && (j == m));
    }
    
    public static void main(String[] args) {
        Boolean res1 = validWordAbbreviation("internationalization", "i12iz4n");
        System.out.println("Res 1 ==> " + res1);
        
        Boolean res2 = validWordAbbreviation("apple", "a2e");
        System.out.println("Res 2 ==> " + res2);
    }
}
