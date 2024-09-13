//https://leetcode.com/discuss/interview-question/5740653/Google-Software-Engineer-L4-(Bangalore)oror-Rejected

/*
Given an array of stock prices, find the size of the widest interval over which the stock has lost value. Lost value is defined as the initial value of the interval is larger than the final value of the interval. Intermediate values within the interval may rise above the initial value, but the interval would still be considered as lost value.

Example :
Time: 00, 01, 02, 03, 04, 05, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16
Price: 50, 52, 58, 54, 57, 51, 55, 60, 62, 65, 68, 72, 62, 61, 59, 63, 72

Ans - 7
Explanation - the widest interval with a net loss in value is from the indices 07 to 14 and has length 14 - 7 = 7
Although a peak value of 72 at time index 11 is present in this interval, it is still considered an interval with loss value.
*/

int solve(vector<int> prices) {
    int res = 0;
    stack<int> stk;
    for(int i=0; i<prices.size(); i++) {
        if(stk.empty()) {
            stk.push(i);
            continue;
        }
        while(!stk.empty() && prices[stk.top()] > prices[i]) {
            stk.pop();
        }
        if(!stk.empty()) {
            res = max(res, i - stk.top());
        }
        stk.push(i);
    }
    return res != 0 ? res-1 : res;
}


int main() {
    vector<int> prices = {50, 52, 58, 54, 57, 51, 55, 60, 62, 65, 68, 72, 62, 61, 59, 63, 72};
    int res = solve(prices);
    cout<<res<<"\n";
}
