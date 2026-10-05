/*
Given an array arr[] of length N, the task is to find the Bitwise OR of the sum of all possible subsequences from the given array.

Examples:

Input: arr[] = {4, 2, 5}
Output: 15
Explanation: All subsequences from the given array and their corresponding sums:
{4} - 4
{2} - 2
{5} - 5
{4, 2} - 6
{4, 5} - 9
{2, 5} - 7
{4, 2, 5} -11
Therefore, the Bitwise OR of all sums = 4 | 2 | 5 | 6 | 9 | 7 | 11 = 15.

Input: arr[] = {1, 9, 8}
Output: 27
Explanation: All subsequences from the given array and their corresponding sums:
{1} - 1
{9} - 9
{8} - 8
{1, 9} - 10
{9, 8} - 17
{1, 8} - 9
{1, 9, 8} - 18
Therefore, Bitwise OR of all sums = 1 | 9 | 8 | 10 | 17 | 9 | 18 = 27.
*/

class Solution {
public:
    long long bitwiseSubArraySum(vector<int> nums) {
        long long prefixSum = 0;
        long long res = 0;
        for(auto num: nums) {
            prefixSum += num;
            res |= (long long) num | prefixSum;
        }
        return res;
    }
};
int main() {
    Solution s;
    vector<int> nums = {4, 2, 5};
    long long sum = s.bitwiseSubArraySum(nums);
    cout<<sum<<"\n";
    
    nums = {1, 9, 8};
    sum = s.bitwiseSubArraySum(nums);
    cout<<sum<<"\n";
}
