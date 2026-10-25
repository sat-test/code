/*
Max consecutive 1's in circular format. https://leetcode.com/problems/max-consecutive-ones-ii/description/ replacing 1's
*/

class Solution {
public:
    int maxConsecutiveOncesII(vector<int> nums, int K) {
        int n = nums.size();
        if (n == 0) return 0;
        if (K >= n) return n;
        
        int k = K, i = 0, j = 0, res = 0;
        
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
                ++i;
            }
            res = max(res, j-i);
        }
        return res;
    }
    
    int maxConsecutiveOncesIICircluar(vector<int> nums, int K) {
        int n = nums.size();
        if (n == 0) return 0;
        if (K >= n) return n;
        
        int k = K, i = 0, j = 0, res = 0;
        
        while(j < 2*n && j-i < n) {
            if(nums[j%n] == 1) {
                ++j;
            } else if(k > 0) {
                ++j;
                --k;
            } else {
                if(nums[i%n] == 0 && k < K) {
                    ++k;
                }
                ++i;
            }
            res = max(res, j-i);
        }
        return res;
    }
};

int main() {
    Solution s;
    
    vector<int> nums1 = {1,0,1,1,0,1,1};
    int res1 = s.maxConsecutiveOncesII(nums1, 1);
    int res2 = s.maxConsecutiveOncesIICircluar(nums1, 1);
    cout<<res1<<" "<<res2<<"\n";
}
