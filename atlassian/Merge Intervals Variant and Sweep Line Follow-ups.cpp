/*
11. Merge Intervals Variant + Sweep Line Follow-ups
Problem Statement
You are given a list of intervals, where each interval represents a time range:
[start, end]

Merge all overlapping intervals and return the resulting set of non-overlapping intervals.
Two intervals are considered overlapping if:
next.start <= current.end

After merging, return the intervals sorted by their start time.
Input
vector<vector<int>> intervals

where each interval contains:
[startTime, endTime]

Constraints
- 1 <= N <= 10^5
- 0 <= startTime < endTime <= 10^9
- Intervals may be given in any order.
- Intervals can have the same start/end time.
- Intervals are inclusive: [1, 3] and [3, 5] are considered overlapping.
- Expected time complexity: O(N log N)
- Expected space complexity: O(N)
Output
Return a list of merged, non-overlapping intervals sorted by start time.
Example 1
Input:
intervals = {
    {1, 3},
    {2, 6},
    {8, 10},
    {9, 12}
}

Processing:
[1,3] + [2,6]   -> [1,6]
[8,10] + [9,12] -> [8,12]

Output:
{
    {1, 6},
    {8, 12}
}
*/

class Solution {
public:
    vector<vector<int>> mergeIntervals(vector<vector<int>> intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res;

        for (auto interval : intervals) {
            int start = interval[0];
            int end = interval[1];

            if (res.empty() || res.back()[1] < start) {
                res.push_back({start, end});
            } else {
                res.back()[1] = max(res.back()[1], end);
            }
        }

        return res;
    }
    
    int maxOverlappingIntervals(vector<vector<int>>& intervals) {
        vector<pair<int, int>> events;

        for (auto& interval : intervals) {
            int start = interval[0];
            int end = interval[1];

            events.push_back({start, +1});
            events.push_back({end, -1});
        }

        sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
            if (a.first != b.first)
                return a.first < b.first;

            // Start before end because intervals are inclusive.
            return a.second > b.second;
        });

        int active = 0;
        int maxActive = 0;

        for (auto& [time, delta] : events) {
            active += delta;
            maxActive = max(maxActive, active);
        }

        return maxActive;
    }
};

int main() {
    Solution s;
    
    vector<vector<int>> intervals = {
        {{0,0},{0,1},{2,2}}
    };
    
    vector<vector<int>> res = s.mergeIntervals(intervals);
    for(int i=0; i<res.size(); i++) {
        cout<<res[i][0]<<" "<<res[i][1]<<"\n";
    }
    
    int overlap = s.maxOverlappingIntervals(intervals);
    cout<<overlap<<"\n";

    return 0;
}
