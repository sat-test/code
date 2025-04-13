/*
Game theory question: We are given an integer array and we have two players Alice and Bob and both are playing a game where they can pick either first or last integer from the array. Each player plays optimally. Return the maximum score Alice can score given she plays first.
https://leetcode.com/discuss/post/6536801/uber-sde-2-bangalore-reject-by-abhinavp1-9vjf/
*/

class Solution {
public:
    vector<vector<int>> dp;
    int maxScore(vector<int> &arr, int left, int right) {
        if(left > right) {
            return 0;
        }
        if(dp[left][right] != -1) {
            return dp[left][right];
        }
        int pickLeft = arr[left] + min(maxScore(arr, left + 2, right), maxScore(arr, left + 1, right - 1));
        int pickRight = arr[right] + min(maxScore(arr, left + 1, right - 1), maxScore(arr, left, right - 2));
        dp[left][right] = max(pickLeft, pickRight);
        return dp[left][right];
    }
    
    int maximumAliceScore(vector<int>& stones) {
        int n = stones.size();
        dp = vector<vector<int>>(n, vector<int>(n, -1));
        return maxScore(stones, 0, n - 1);
    }
};

void runTests() {
    Solution sol;

    // Test Case 1: Basic input
    vector<int> stones1 = {3, 9, 1, 2};
    assert(sol.maximumAliceScore(stones1) == 11);
    cout << "Test Case 1 Passed ✅" << endl;

    // Test Case 2: Equal elements
    vector<int> stones2 = {4, 4, 4, 4};
    assert(sol.maximumAliceScore(stones2) == 8);
    cout << "Test Case 2 Passed ✅" << endl;

    // Test Case 3: Alice should skip high value to deny Bob
    vector<int> stones3 = {20, 30, 2, 2, 2, 10};
    assert(sol.maximumAliceScore(stones3) == 42);
    cout << "Test Case 3 Passed ✅" << endl;

    // Test Case 4: Single element
    vector<int> stones4 = {5};
    assert(sol.maximumAliceScore(stones4) == 5);
    cout << "Test Case 4 Passed ✅" << endl;

    // Test Case 5: Two elements
    vector<int> stones5 = {1, 100};
    assert(sol.maximumAliceScore(stones5) == 100);
    cout << "Test Case 5 Passed ✅" << endl;

    // Test Case 6: Large values
    vector<int> stones6 = {1000, 1, 1000};
    assert(sol.maximumAliceScore(stones6) == 1001);
    cout << "Test Case 6 Passed ✅" << endl;

    // Test Case 7: Bob will always lose
    vector<int> stones7 = {1, 2, 3, 4, 5};
    assert(sol.maximumAliceScore(stones7) == 9); // Alice picks 1 → Bob picks 5 → Alice picks 4 → Bob picks 3 → Alice picks 2
    cout << "Test Case 7 Passed ✅" << endl;
}


int main() {
    runTests();
    return 0;
}
