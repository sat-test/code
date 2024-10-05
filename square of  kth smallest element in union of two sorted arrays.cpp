/*

Given a sorted array with positive and negative values, sort them based on the square of its values. Also, print the squared values array.

Expected O(N) working code and interviewer made me run the code with sample tests and compare output
Sample: [-7, -2, -1, -1, 1, 2, 2, 2, 3, 5] => [-1, -1, 1, -2, 2, 2, 2, 3, 5, -7]
Now, given the same array, how would you modify your code to find the kth smallest square element in the array. Expected O(LogN)
The problem can be reduced to finding the kth smallest element in union of two sorted arrays similar to median of two sorted arrays

https://leetcode.com/discuss/interview-experience/5870808/Uber-or-SDE-2-or-Bangalore-or-Sep-2024-Reject
https://leetcode.com/problems/squares-of-a-sorted-array/description/
https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1
*/

int findStartingPositiveInd(vector<int> arr) {
    return lower_bound(arr.begin(), arr.end(), 0) - arr.begin();
}

// Binary search function to find the k-th smallest square element
int findKthElement(vector<int> A, int negSize, int posSize, int negStart, int posStart, int k) {
    int low = 0;
    int high = min(k, posSize); // Ensure we don't go beyond the positive size

    while (low <= high) {
        int cut1 = (low + high) >> 1; // Number of elements from positive side
        int rem = k - cut1;  // Remaining elements must come from negative side

        // Handle when rem is too large for negatives
        if (rem > negSize) {
            low = cut1 + 1;
            continue;
        }

        int cut2 = rem; // Number of elements from the negative side (in reverse order)

        // Calculate boundaries (squared values)
        int l1 = (cut1 == 0) ? INT_MIN : A[posStart + cut1 - 1] * A[posStart + cut1 - 1];
        int r1 = (cut1 == posSize) ? INT_MAX : A[posStart + cut1] * A[posStart + cut1];

        int l2 = (cut2 == 0) ? INT_MIN : A[negStart - cut2 + 1] * A[negStart - cut2 + 1];
        int r2 = (cut2 == negSize) ? INT_MAX : A[negStart - cut2] * A[negStart - cut2];

        // If valid partition, return the smaller of the right mins
        if (l1 <= r2 && l2 <= r1) {
            return min(r1, r2);
        } else if (l1 > r2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }

    return -1;
}

// Main function to solve the k-th smallest square problem
int solve(vector<int> A, int k) {
    k = k-1;
    int n = A.size();
    int ind = findStartingPositiveInd(A); // Find the first non-negative index

    // Edge case: if no negative numbers
    if (ind == 0) {
        return A[k - 1] * A[k - 1];
    }
    // Edge case: if no positive numbers
    if (ind == n) {
        return A[n - k] * A[n - k];
    }

    // Call the binary search function to get the k-th smallest square
    return findKthElement(A, ind, n - ind, ind - 1, ind, k);
}

// Test the function with an example
int main() {
    vector<int> A = {-7, -2, -1, -1, 1, 2, 2, 2, 3, 5};
    int k = 10;
    int res = solve(A, k);
    cout << res << "\n";  // Output: 4 (since 4 is the 4th smallest square: [-7^2, -2^2, -1^2, 2^2] -> 49, 4, 1, 4)
    return 0;
}
