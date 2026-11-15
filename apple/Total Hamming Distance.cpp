/*
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Given an integer array nums, return the sum of Hamming distances between all the pairs of the integers in nums.

Example 1:

Input: nums = [4,14,2]
Output: 6
Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case).
The answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Example 2:

Input: nums = [4,14,4]
Output: 4
*/

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int n = nums.size();
        vector<int> vec(32, 0);
        for(int i=0; i<n; i++) {
            int num = nums[i];
            int pos = 0;
            while(pos < 32 && num) {
                if(num&1) {
                    ++vec[pos];
                }
                num >>= 1;
                ++pos;
            }
        }
        int res = 0;
        for(int i=0; i<32; i++) {
            res += vec[i] * (n - vec[i]);
        }
        return res;
    }
};
