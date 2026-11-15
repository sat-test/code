/*
Given a signed 32-bit integer x, return x with its digits reversed. If reversing x causes the value to go outside the signed 32-bit integer range [-2^31, 2^31 - 1], then return 0.

Assume the environment does not allow you to store 64-bit integers (signed or unsigned).

Example 1:

Input: x = 123
Output: 321
Example 2:

Input: x = -123
Output: -321
Example 3:

Input: x = 120
Output: 21

*/

class Solution {
public:
    int reverse(int x) {
        int res = 0;

        while (x) {
            int r = x % 10;
            x /= 10;

            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && r > 7))
                return 0;

            if (res < INT_MIN / 10 || (res == INT_MIN / 10 && r < -8))
                return 0;

            res = res * 10 + r;
        }

        return res;
    }
};
