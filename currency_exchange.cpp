/*

Question
Paramenters:


array of currency conversion rates. E.g. ['USD', 'GBP', 0.77] which means 1 USD is equal to 0.77 GBP
an array containing a 'from' currency and a 'to' currency
Given the above parameters, find the conversion rate that maps to the 'from' currency to the 'to' currency.
Your return value should be a number.


Example:
You are given the following parameters:


Rates: ['USD', 'JPY', 110] ['US', 'AUD', 1.45] ['JPY', 'GBP', 0.0070]
To/From currency ['GBP', 'AUD']
Find the rate for the 'To/From' curency. In this case, the correct result is 1.89.

https://leetcode.com/discuss/interview-question/483660/google-phone-currency-conversion

*/


float findExchange(vector<pair<string,string>> currency, vector<float> rates, pair<string, string> exchange) {
    unordered_map<string, unordered_map<string, float>> m;
    int n = currency.size();
    for(int i=0; i<n; i++) {
        string from = currency[i].first;
        string to = currency[i].second;
        float rate = rates[i];
        m[from][to] = rate;
        m[to][from] = 1/rate;
    }
    
    string exchangeFrom = exchange.first;
    string exchangeTo = exchange.second;
    
    queue<pair<string, float>> q;
    unordered_set<string> s;
    
    q.push({exchangeFrom, 1.0});
    
    while(!q.empty()) {
        string curr = q.front().first;
        float rate = q.front().second;
        // cout<<curr<<" "<<rate<<"\n";
        q.pop();
        if(curr == exchangeTo) {
            return rate;
        }
        s.insert(curr);
        for(auto it : m[curr]) {
            if(s.find(it.first) == s.end()) {
                float r = rate * it.second;
                q.push({it.first, r});
            }
        }
    }
    
    return -1;
}


int main() {
    vector<pair<string,string>> currency = {{"USD", "JPY"}, {"USD", "AUD"}, {"JPY", "GBP"}};
    vector<float> rates = {110, 1.45, 0.0070};
    pair<string, string> exchange = {"GBP", "AUD"};
    float exchangeRates = findExchange(currency, rates, exchange);
    cout<<exchange.first<<" - "<<exchange.second<<" : "<<exchangeRates<<"\n";
}
