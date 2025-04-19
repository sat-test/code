/*
We are given an array, minRange, maxRange. Need to count number of subarrays which have both minRange and maxRange inside them and all other elements in the subarray should be between the range.


Problem Statement
Given:

An array of integers nums.

Two integers: minRange and maxRange.

You need to count all subarrays that satisfy the following conditions:

The minimum value in the subarray must be minRange.

The maximum value in the subarray must be maxRange.

All elements in the subarray must be between minRange and maxRange (inclusive).
*/

int solve(vector<int> vec, int left, int right) {
    int i = 0, j = 0, n = vec.size(), res = 0;
    unordered_map<int, int> m;
    while(i < n && j < n) {
        // cout<<i<<" "<<j<<"\n";
        if(vec[j] < left || vec[j] > right) {
            j += 1;
            i = j;
            m[left] = 0;
            m[right] = 0;
            continue;
        }
        ++m[vec[j]];
        if(m[left] > 0 && m[right] > 0) {
            ++res;
            if(i != j) {
                --m[vec[i]];
                --m[vec[j]];
                ++i;
            } else {
                ++j; 
            }
        } else {
            ++j;
        }
        // cout<<res<<"\n";
    }
    
    while(i < n) {
        --m[vec[i]];
        if(m[left] > 0 && m[right] > 0) {
            ++res;
        }
        ++i;
    }
    
    return res;
}

int main() {
    vector<int> vec = {1, 2, 2, 5, 2, 5};
    int left = 2, right = 5;
    cout<<solve(vec, left, right)<<"\n";
}
