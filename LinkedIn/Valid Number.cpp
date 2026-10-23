/*
Given a string s, return whether s is a valid number.

For example, all the following are valid numbers: "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", while the following are not valid numbers: "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53".

Formally, a valid number is defined using one of the following definitions:

An integer number followed by an optional exponent.
A decimal number followed by an optional exponent.
An integer number is defined with an optional sign '-' or '+' followed by digits.

A decimal number is defined with an optional sign '-' or '+' followed by one of the following definitions:

Digits followed by a dot '.'.
Digits followed by a dot '.' followed by digits.
A dot '.' followed by digits.
An exponent is defined with an exponent notation 'e' or 'E' followed by an integer number.

The digits are defined as one or more digits.

*/

class Solution {
public:
    bool isNumber(string s) {
        int n = s.size();
        int countE = 0;   // count of 'e' or 'E'
        int countD = 0;   // count of '.'
        int countN = 0;   // count of digits before exponent
        int countAE = 0;  // count of digits after exponent
        
        for(int i=0; i<n; i++) {
            if(s[i] == '.') countD++;
            if(s[i] == 'e' || s[i] == 'E')  countE++;
            if(isdigit(s[i])) {
                if(countE) countAE++;
                else countN++;
            }

            if((s[i] == '+' || s[i] == '-') && i != 0 && (s[i-1] != 'e' && s[i-1] != 'E'))  return false;
            else if(isalpha(s[i]) && (s[i] != 'e' && s[i] != 'E')) return false;
            else if(countD > 1 || countE > 1) return false;
            else if(s[i] == '.' && countE) return false;
            else if((i == 0 || i == n-1) && (s[i] == 'e' || s[i] == 'E')) return false;
            else if(i == 0 && i == n-1 && s[i] == '.') return false;
            else if((s[i] == 'e' || s[i] == 'E') && !countN) return false;
        }

        if((countE && !countAE) || !countN) return false;
        return true;
    }
};
