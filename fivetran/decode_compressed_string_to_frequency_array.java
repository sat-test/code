/*
Question
The input string contains digits 0-9 and parentheses (). The digits outside the parentheses are mapped to lowercase English alphabets. The digits inside the parentheses are mapped to the frequencies of the corresponding alphabets in the order that they appear in the string .

Example 1
Input string: '1224#26#'
This input string is an encoding of 'abxz'.

'a' to 'i' is encoded from '0' to '9' respectively. So, '1' maps to 'a' and '2' maps to 'b'.
'j' is encoded as '10#', 'k' as '11#', and so on, with the last alphabet 'z' as '26#'.
Example 2
Input string: '1(2)2(3)324#26#(5)'
This input string is an encoding of 'aabbbcxzzzzz'

The encoding is similar to the example above except the parentheses contain the frequency of each corresponding character when it's greater than 1. For example,

('->' stands for 'maps to')
In 'aa', a is seen 2 times, so a -> 1 and 2 times -> (2); therefore 'aa' becomes 1(2).
In 'zzzzz', z is seen 5 times, so z -> 26# and 5 times -> (5); therefore 'zzzzz' becomes 26#(5).

Return

Given a string, return a frequency array containing the counts of the alphabets in the string.

For example, the input string 'abxz' should return:

[1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1] -> You need to return this array.
[a.b................................................................x....z] -> I drew this for your convenience.



*/
class Solution {
    int[] frequencyList(String input) {
        int[] freq = new int[26];
        int n = input.length();
        int i = n-1;
        while(i >= 0) {
            int f = 1;
            if(input.charAt(i) == ')') {
                --i;
                f = 0;
                int p = 1;
                while(input.charAt(i) != '(') {
                    f = p * (input.charAt(i) - '0') + f;
                    p *= 10;
                    --i;
                }
                --i;
            } 
            
            int num = 0;
            if(input.charAt(i) == '#') {
                --i;
                if(i > 0 && input.charAt(i - 1) >= '1' && input.charAt(i - 1) <= '2') {
                    num = (input.charAt(i - 1) - '0') * 10 + (input.charAt(i) - '0');
                    i -= 2;
                } else {
                    num = input.charAt(i) - '0';
                    --i;
                }                
            } else {
                num = input.charAt(i) - '0';
                --i;
            }
            
            freq[num-1] += f;
        }
        
        return freq;
    }
}


public class Main {

    static void printResult(String input, int[] expected) {
        Solution solution = new Solution();

        int[] actual = solution.frequencyList(input);

        System.out.println("Input:    " + input);
        System.out.println("Expected: " + java.util.Arrays.toString(expected));
        System.out.println("Actual:   " + java.util.Arrays.toString(actual));

        System.out.println(
            java.util.Arrays.equals(actual, expected)
                ? "PASS"
                : "FAIL"
        );

        System.out.println();
    }

    public static void main(String[] args) {

        // Example 1: abxz
        printResult(
            "1224#26#",
            new int[] {
                1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 1
            }
        );

        // Example 2: aabbbcxzzzzz
        printResult(
            "1(2)2(3)324#26#(5)",
            new int[] {
                2, 3, 1, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 0, 5
            }
        );

        // Single character: a
        printResult(
            "1",
            new int[] {
                1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0
            }
        );

        // a repeated 5 times
        printResult(
            "1(5)",
            new int[] {
                5, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0
            }
        );

        // z repeated 10 times
        printResult(
            "26#(10)",
            new int[] {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 10
            }
        );
    }
}
