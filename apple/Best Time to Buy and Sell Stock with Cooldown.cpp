/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:

After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

Example 1:

Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]
Example 2:

Input: prices = [1]
Output: 0
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0)  return 0;
        int n = prices.size();
        vector<int> buy(n+1, 0);
        vector<int> sell(n+1, 0);
        buy[1] = -prices[0];
        for(int i=2; i<=n; i++) {
            int price = prices[i-1];
            buy[i] = max(sell[i-2] - price, buy[i-1]);
            sell[i] = max(sell[i-1], buy[i-1] + price);
        }
        return sell[n];
    }
};
