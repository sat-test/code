/*
Problem statement
Stark Industry is planning to organize Stark Expo, for which various departments have to organize meetings to check their preparations. Since Stark Tower has limited rooms available for the meeting, Tony decided to allot a room to each meeting so that all the meetings are organized in the least possible conference rooms, and a the moment, only one meeting will happen in one room. So, he asked JARVIS to allot each meeting a room and tell the minimum number of conference rooms to be reserved. But, since JARVIS was busy rendering another Iron Man suit model, he asked you to help.

You are given an array of integers ARR of size N x 2, representing the start and end time for N meetings. Your task is to find the minimum number of rooms required to organize all the meetings.

Note:

1. You can assume that all the meetings will happen on the same day.
2. Also, as soon as a meeting gets over if some other meeting is scheduled to start at that moment, they can then be allocated that room.
Note:

Try to solve the problem in linear time complexity.
For Example:

Consider there are three meetings scheduled with timings:
1pm - 4pm
3pm - 5pm
4pm - 6pm

At the start of time, meeting 1 will be allotted room 1, which will be occupied till 4 pm hence for meeting 2 we’ll have to provide another room. At 4 pm, meeting 3 can be organized in room 1 because by that time, meeting 1 would have ended. Hence we’ll require two rooms for holding all three meetings.

*/

#include <bits/stdc++.h> 
int minRooms(vector<vector<int>> intervals) {
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0; i<intervals.size(); i++) {
        int start = intervals[i][0];
        int end = intervals[i][1];
        if(pq.empty() || pq.top() > start) {
            pq.push(end);
        } else {
            pq.pop();
            pq.push(end);
        }
    }
    return pq.size();
}
