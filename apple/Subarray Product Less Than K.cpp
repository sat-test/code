/*
You are given an array of integers nums and an integer k.

Return the number of contiguous subarrays where the product of all the elements in the subarray is strictly less than k.

Example 1:

Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
Example 2:

Input: nums = [1,2,3], k = 0
Output: 0

*/

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        int i = 0, j = 0, n = nums.size();
        long long curr = 1;
        int res = 0;

        while(j < n) {
            curr *= nums[j];
            while (curr >= k) {
                curr /= nums[i];
                i++;
            }
            res += (j - i + 1);
            j++;
        }
        return res;
    }
};
