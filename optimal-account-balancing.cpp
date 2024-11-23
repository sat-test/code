/*
465. Optimal Account Balancing
Description
You are given an array of transactions transactions where transactions[i] = [fromi, toi, amounti] indicates that the person with ID = fromi gave amounti to the person with ID = toi.

Return the minimum number of transactions required to settle the debt.

Example 1:

Input: transactions = [[0,1,10],[2,0,5]]
Output: 2
Explanation:
Person #0 gave person #1 10.
Person #2 gave person #0 5.
Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 5 each.
Example 2:

Input: transactions = [[0,1,10],[1,0,1],[1,2,5],[2,0,5]]
Output: 1
Explanation:
Person #0 gave person #1 10.
Person #1 gave person #0 1.
Person #1 gave person #2 5.
Person #2 gave person #0 5.
Therefore, person #1 only need to give person #0 4, and all debt is settled.

https://leetcode.com/problems/optimal-account-balancing/
https://leetcode.ca/2017-03-09-465-Optimal-Account-Balancing/#google_vignette
*/

int minTransfers(vector<vector<int>>& transactions) {
    int g[12]{};
    for (auto& t : transactions) {
        g[t[0]] -= t[2];
        g[t[1]] += t[2];
    }
    vector<int> nums;
    for (int x : g) {
        if (x) {
            nums.push_back(x);
        }
    }
    int m = nums.size();
    int f[1 << m];
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for(int i=1; i< 1<<m; ++i) {
        int s = 0;
        for (int j = 0; j < m; ++j) {
            if (i >> j & 1) {
                s += nums[j];
            }
        }
        if (s == 0) {
            f[i] = __builtin_popcount(i) - 1;
            for (int j = (i - 1) & i; j; j = (j - 1) & i) {
                f[i] = min(f[i], f[j] + f[i ^ j]);
            }
        }
    }
    return f[(1 << m) - 1];
}

int main() {
    vector<vector<int>> A = {{0,1,10},{1,0,1},{1,2,5},{2,0,5}};
    int res = minTransfers(A);
    cout<<res<<"\n";
}
