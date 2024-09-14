/*
There is a bank which has a fund of X dollars. The bank has to serve N customers one by one who may either deposit/withdraw money.
The bank must stop serving any more customers if it meets a customer with withdrawal request exceeding the current funds.

Also, the bank has the power to refuse service to any number of customers but once the bank starts from any arbitrary customer,
it continues serving each customer after that customer and can only stop if it is unable to make a withdrawal request greater than the bank's funds at that point of time.

What is the maximum number of people the bank can serve?

First line will contain bank's initial fund: X
Second line will contain number of customers: N
Each of the next N lines contain a possible transaction: R. If R is negative, then it is a deposit to the bank, else it is a withdrawal.

constraints - n <=10^5


https://leetcode.com/discuss/interview-question/5650107/Google-L3-or-SWE2-Tech-2
https://leetcode.com/discuss/interview-question/5254599/Google-L3-interview-question/
*/

int solve(vector<int> A, int initialAmount) {
    int n = A.size();
    // for(int i=0; i<n; i++) {
    //     A[i] = -A[i];
    // }
    vector<int> preSum(n);
    for(int i=0; i<n; i++) {
        if(i == 0) {
            preSum[i] = A[i];
        } else {
            preSum[i] = preSum[i-1] + A[i];
        }
    }
    multiset<int> s;
    int res = 0;
    int l = 0, r = 0;
    while(r < n) {
        s.insert(preSum[r++]);
        int val = preSum[l] - (A[l]+initialAmount) - 1;
        while(r < n) {
            s.insert(preSum[r]);
            int mini = *s.begin();
            if(mini <= val) {
                break;
            }
            res = max(res, r-l+1);
            ++r;
        }
        s.erase(preSum[l]);
        ++l;
    }
    
    return res;
}

int main() {
    vector<int> A = {1, -3, 5, -2, 4, -7, 2, -3};
    int a = 1;
    vector<int> B = {1, -3, 5, -2, 1};
    int b = 1;
    vector<int> C = {4, 1, 1, 1, 1};
    int c = 4;
    int res;
    res = solve(A, a);
    cout<<res<<"\n";
    // res = solve(B, b);
    // cout<<res<<"\n";
    // res = solve(C, c);
    // cout<<res<<"\n";
}
