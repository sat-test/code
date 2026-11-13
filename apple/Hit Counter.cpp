/*
Problem statement
You have to design a hit counter which supports the functionality of accepting a hit and returning the number of hits done in the last 5 minutes. Each call is made with a timestamp which is given in seconds.

It is possible to receive several hit arriving at the same time. All the calls are done in chronological order. The timestamp for a call is equal to or greater than the Timestamp for the call just before it. Timestamp at the start can be considered as 0.

For example:

The counter is hit at 'T'  = 1
The counter is hit at 'T' = 50
The getHit function at 'T' = 100 returns 2
The counter is hit at 'T' = 250
The getHit function at 'T' = 100 returns 2
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 100
1 <= N <= 5 * 10^3
1 <= STAMP <= 10 ^ 9
*/

#include <bits/stdc++.h> 
class hitCounter {
    private:
        deque<pair<int, int>> dq;
        int total = 0;
    public:
        void hit(int timestamp) {
            if(!dq.empty() && dq.back().first == timestamp) {
                dq.back().second++;
            } else {
                dq.push_back({timestamp, 1});
            }
            ++total;
        }

        int getHits(int timestamp) {
            while(!dq.empty() && dq.front().first < (timestamp - 300)) {
                total -= dq.front().second;
                dq.pop_front();
            }
            return total;
        }
};
