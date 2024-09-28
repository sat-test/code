/*
Find leftmost smaller number in an array.
Suppose you are given an array [2, 1, 3, 2, 1, 3]
output should be [-1, -1, 2, 1, -1, 2]?

Constraints are each element of array must be in range 1 <= arr[i] <= m ?
Expected time complexity O(n + m).

https://leetcode.com/discuss/interview-question/algorithms/125078/find-leftmost-smaller-number-in-an-array

*/

#include <iostream>
#include <vector>
#include <climits>  // For INT_MAX

using namespace std;

vector<int> findLeftmostSmaller(const vector<int>& input, int m) {
    int n = input.size();
    vector<int> arr(m + 1, INT_MAX);  // Initialize array of size m+1 with INT_MAX
    vector<int> result(n, -1);        // To store the result, initialized to -1

    // Step 1: Traverse input array left to right and fill `arr`
    for (int i = 0; i < n; ++i) {
        int x = input[i];
        arr[x] = min(arr[x], i);  // Store the smallest index where element x occurs
    }

    // Step 2: Refine `arr` to hold smallest index of any number smaller than or equal to x
    for (int x = 1; x <= m; ++x) {
        arr[x] = min(arr[x], arr[x - 1]);
    }

    // Step 3: Traverse input array again to compute the result
    for (int i = 0; i < n; ++i) {
        int x = input[i];
        if (arr[x - 1] < i) {  // Check if there's a smaller element to the left
            result[i] = input[arr[x - 1]];  // Get the value of the smaller element
        }
    }

    return result;
}

int main() {
    vector<int> input = {2, 1, 3, 2, 1, 3};
    int m = 3;  // Maximum value in the input array

    vector<int> result = findLeftmostSmaller(input, m);

    // Output the result
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
