/*
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.

 

Example 1:

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6
Explanation: [1,1,1,0,0,1,1,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
Example 2:

Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10
Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.

*/

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int i = 0, j = 0, K = k, n = nums.size(), res = 0;
        while(j < n) {
            if(nums[j] == 1) {
                ++j;
            } else if(k > 0) {
                ++j;
                --k;
            } else {
                if(nums[i] == 0 && k < K) {
                    ++k;
                } 
                if(i == j) {
                    ++j;
                } 
                ++i;
            }
            res = max(res, j-i);
        }
        return res;
    }
};
