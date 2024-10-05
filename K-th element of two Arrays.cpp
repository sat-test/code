/*
https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1
https://leetcode.com/discuss/interview-experience/5870808/Uber-or-SDE-2-or-Bangalore-or-Sep-2024-Reject
*/

class Solution {
  public:
    int solve(vector<int> A1, vector<int> A2, int n, int m, int k) {
        if(n > m) {
            return solve(A2, A1, m, n, k);
        }
        int low = max(0, k-m);
        int high = min(k, n);
        while(low <= high) {
            int cut1 = (low+high)>>1;
            int cut2 = (k - cut1);
            int l1 = cut1 == 0 ? INT_MIN : A1[cut1-1];
            int l2 = cut2 == 0 ? INT_MIN : A2[cut2-1];
            int r1 = cut1 == n ? INT_MAX : A1[cut1];
            int r2 = cut2 == m ? INT_MAX : A2[cut2];
            
            if(l1 <= r2 && l2 <= r1) {
                return max(l1, l2);
            } else if(l1 > r2) {
                high = cut1-1;
            } else {
                low = cut1+1;
            }
        }
        return 1;
    }
    int kthElement(int k, vector<int>& arr1, vector<int>& arr2) {
        return solve(arr1, arr2, arr1.size(), arr2.size(), k);
    }
};
