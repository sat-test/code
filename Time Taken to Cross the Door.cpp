/*
https://leetcode.com/problems/time-taken-to-cross-the-door/description/
https://leetcode.ca/2023-03-02-2534-Time-Taken-to-Cross-the-Door/
*/

#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> timeTaken(vector<int>& arrival, vector<int>& state) {
        vector<int> narrResult(arrival.size());
        
        // Min-heaps for exit and enter queues
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> exitQ;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> enterQ;

        // Populate the queues with persons (arrival time, index)
        for (int i = 0; i < arrival.size(); i++) {
            if (state[i] == 0)
                enterQ.push({arrival[i], i});
            else
                exitQ.push({arrival[i], i});
        }

        int nExit = 2;  // Initially allow exit
        int nSecond = 0;

        // Process both queues while neither is empty
        while (!exitQ.empty() && !enterQ.empty()) {
            pair<int, int> P;

            if (exitQ.top().first <= nSecond && enterQ.top().first <= nSecond) {
                if (nExit != 0) {
                    P = exitQ.top();
                    exitQ.pop();
                    nExit = 1;
                } else {
                    P = enterQ.top();
                    enterQ.pop();
                    nExit = 0;
                }
                narrResult[P.second] = nSecond;
            } 
            else if (exitQ.top().first <= nSecond) {
                P = exitQ.top();
                exitQ.pop();
                nExit = 1;
                narrResult[P.second] = nSecond;
            } 
            else if (enterQ.top().first <= nSecond) {
                P = enterQ.top();
                enterQ.pop();
                nExit = 0;
                narrResult[P.second] = nSecond;
            } 
            else {
                // Nothing can happen, so allow exit
                nExit = 1;
            }

            nSecond++;
        }

        // Process remaining exit queue
        while (!exitQ.empty()) {
            if (exitQ.top().first <= nSecond) {
                pair<int, int> P = exitQ.top();
                exitQ.pop();
                narrResult[P.second] = nSecond;
            }
            nSecond++;
        }

        // Process remaining enter queue
        while (!enterQ.empty()) {
            if (enterQ.top().first <= nSecond) {
                pair<int, int> P = enterQ.top();
                enterQ.pop();
                narrResult[P.second] = nSecond;
            }
            nSecond++;
        }

        return narrResult;
    }
};



int main() {
    vector<int> arrival = {0, 1, 1, 2, 4};
    vector<int> state = {0, 1, 0, 0, 1};  
    Solution sol;
    vector<int> res = sol.timeTaken(arrival, state);
    for(int i=0; i<res.size(); i++) {
        cout<<res[i]<<" ";
    }
}
