/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.

Example 1:

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
Example 2:

Input: height = [4,2,0,3,2,5]
Output: 9

*/

class Solution {
public:
    int trap(vector<int>& height) {
        int i=0, n = height.size(), res = 0, curr = 0, leftMaxi = 0, rightMaxi = 0;
        vector<int> left(n, 0);
        vector<int> right(n, 0);

        for(int i=0; i<n; i++) {
            leftMaxi = max(leftMaxi, height[i]);
            left[i] = leftMaxi;
            rightMaxi = max(rightMaxi, height[n-i-1]);
            right[n-i-1] = rightMaxi;
        }

        for(i=0; i<n; i++) {
            curr = min(left[i], right[i]) - height[i];
            res += curr;
        }

        return res;
    }
};
