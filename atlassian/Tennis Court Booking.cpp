/*
4. Tennis Court Booking
You are designing a tennis court booking system for a sports facility that has multiple courts.
Each booking request contains:
(startTime, endTime)

A booking can be assigned to any available tennis court, but two bookings cannot use the same court if their time intervals overlap.
Task
Given a list of booking requests, determine whether each booking can be accommodated and, if possible, assign it to an available court.
For each booking:
- If an existing court is free during the requested interval, assign the booking to that court.
- Otherwise, if another court is available, assign the booking there.
- If all courts are occupied during that interval, the booking cannot be accommodated.
Example
Suppose the facility has 2 tennis courts and receives:
Booking 1: 10:00 - 11:00
Booking 2: 10:30 - 11:30
Booking 3: 11:00 - 12:00

A possible allocation is:
Court 1:
    Booking 1 → 10:00 - 11:00
    Booking 3 → 11:00 - 12:00

Court 2:
    Booking 2 → 10:30 - 11:30

Booking 3 can use Court 1 because a booking ending at 11:00 does not overlap with one starting at 11:00.
Follow-up 1
Instead of knowing the number of courts beforehand, find the minimum number of courts required to accommodate all booking requests.
Follow-up 2
Given a fixed number of courts, return the court assigned to each booking, or indicate that the booking cannot be accommodated.
Follow-up 3
Support additional booking operations such as:
- Cancel an existing booking.
- Add a new booking after cancellations.
- Check whether a particular time interval is available.
- Find the earliest available court/time slot.
Core DSA concept: This is essentially an interval scheduling / meeting-rooms problem, with extensions around court allocation and dynamic booking management.


Tennis Court Booking
Input
You are given:
vector<pair<int, int>> bookings

where each pair represents:
(startTime, endTime)

You are also given:
int k

representing the number of available tennis courts.
Example:
k = 2

bookings = {
    {10, 11},
    {10, 12},
    {11, 13},
    {12, 14}
}

Constraints
For a reasonable coding-round version:
1 <= k <= 10^5
1 <= n <= 10^5
0 <= startTime < endTime <= 10^9

Each booking has:
startTime < endTime

These are practice constraints, not verified constraints from the original Atlassian report.

Output
For each booking, determine whether it can be assigned to one of the k courts.
Return something like:
vector<int>

where:
result[i] = court number assigned to booking i

and:
-1 = booking cannot be accommodated

For example:
k = 2

bookings:
[10,11]
[10,12]
[11,13]
[12,14]

One valid output could be:
[1, 2, 1, 2]

Meaning:
Booking 1 → Court 1
Booking 2 → Court 2
Booking 3 → Court 1
Booking 4 → Court 2

because:
Court 1: [10,11], [11,13]
Court 2: [10,12], [12,14]

There is no overlap on either court.
*/

class Solution {
public:
    vector<int> tennisCourtBooking(vector<vector<int>> bookings, int k) {

        int n = bookings.size();

        // {start, end, originalIndex}
        vector<array<int, 3>> events;

        for (int i = 0; i < n; i++) {
            events.push_back({
                bookings[i][0],
                bookings[i][1],
                i
            });
        }

        sort(events.begin(), events.end());

        // {availableTime, courtNumber}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        for (int court = 1; court <= k; court++) {
            pq.push({0, court});
        }

        vector<int> res(n, -1);

        for (auto &[start, end, index] : events) {

            auto [lastEnd, court] = pq.top();

            if (start >= lastEnd) {
                pq.pop();

                res[index] = court;

                pq.push({end, court});
            }
        }

        return res;
    }
    
    int minimumTennisCourtRequired(vector<vector<int>> bookings) {

        int n = bookings.size();
        int k = 1;

        // {start, end, originalIndex}
        vector<array<int, 3>> events;

        for (int i = 0; i < n; i++) {
            events.push_back({
                bookings[i][0],
                bookings[i][1],
                i
            });
        }

        sort(events.begin(), events.end());

        // {availableTime, courtNumber}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        pq.push({0, 1});


        for (auto &[start, end, index] : events) {
            auto [lastEnd, court] = pq.top();
            if (start >= lastEnd) {
                pq.pop();
                pq.push({end, court});
            } else {
                pq.push({end, ++k});
            }
        }

        return k;
    }
};

int main() {
    Solution s;
    int k = 2;
    vector<vector<int>> bookings = {
        {10, 11},
        {10, 12},
        {10, 13},
        {12, 14}
    };
    
    vector<int> res = s.tennisCourtBooking(bookings, k);
    for(int i=0; i<res.size(); i++) {
        cout<<res[i]<<"\n";
    }
    
    int res1 = s.minimumTennisCourtRequired(bookings);
    cout<<"Min: "<<res1<<"\n";
}
