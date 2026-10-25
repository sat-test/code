/*
Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b
 

Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3

Output: [1,2,3,4]

Example 2:

Input: arr = [1,1,2,3,4,5], k = 4, x = -1

Output: [1,1,2,3]
*/

class Solution {
private:
    const int inf = 100005;
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int pos = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        if(pos == n) pos = n-1;
        int left = pos, right = pos;
        if(arr[pos] != x && pos != 0) {
            if(abs(arr[pos-1] - x) <= abs(arr[pos]-x)) {
                left = pos-1;
                right = left;
            }
        }

        while(left >= 0 && right < n && right - left + 1 < k) {
            if(left == 0) {
                ++right;
            } else if(right == n-1) {
                --left;
            } else if(abs(arr[left-1] - x) <= abs(arr[right+1]-x)) {
                --left;
            } else {
                ++right;
            }
            // cout<<left<<" "<<right<<"\n";
        }

        vector<int> res;
        for(int i=left; i<=right; i++) {
            res.push_back(arr[i]);
        }
        
        return res;
    }
};
