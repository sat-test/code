/*
https://leetcode.com/discuss/interview-question/5848425/My-Google-SWE-Interview-Experience

Suppose you have given a task to schedule meetings in your office. You have to merge any meeting if they coincides, apart there is a DND interval in which you can't schedule any meeting. If any meeting has time overlapping with DND you have to break it.


You have to do it in
Time Complexity: O(n*log(n))
Space Complexity: O(1)


For e.g
Meeting : [[1, 4], [3, 5], [9, 12], [7, 10]]
DND: [3, 5]


Ans. [[1, 3], [7, 12]]


First merge intervals for Meetings and DHD because overlapping can happend between them


case 1:
M | --------------|
.............D |--------------|
case 2:
............M|----------------|
D. |-------------|
case 3
M. |---------------------|
................D|----------|
case 4
................M|----------|
D |-----------------------|

*/

#include<bits/stdc++.h>
using namespace std;

vector<pair<int, int>> merge_intervals(vector<pair<int, int>>&intervals){
    vector<pair<int, int>>merged_intervals, computation;
    for(auto interval: intervals){
        computation.push_back({interval.first, 0});
        computation.push_back({interval.second, 1});
    }
    sort(computation.begin(), computation.end());
    int cnt = 0;
    int start;
    for(auto elements: computation){
        if(elements.second==0){
            if(cnt==0)
                start=elements.first;
            cnt+=1;
        }
        else{
            cnt-=1;
            if(cnt==0){
                merged_intervals.push_back({start, elements.first});
            }
        }
    }
    return merged_intervals;
}

vector<pair<int, int>> merge_intervals_dhd(vector<pair<int, int>>&meetings, vector<pair<int, int>>&dhd){
    vector<pair<int, int>>new_merged_intervals, computation;
    for(auto interval: meetings){
        computation.push_back({interval.first, 1});
        computation.push_back({interval.second, 2});

    }
    
    for(auto interval: dhd){
        computation.push_back({interval.first, 0});
        computation.push_back({interval.second, 3});
    }
    sort(computation.begin(), computation.end());
    int cnt = 0;
    int start;
    for(auto interval: computation){
        if(interval.second==0){
            if(cnt==1){
                new_merged_intervals.push_back({start, interval.first});
            }
            cnt+=1;
        }
        else if(interval.second==1)
        {
            if(cnt==0){
                start = interval.first;
            }
            cnt+=1;
        }
        else if(interval.second==3){
            if(cnt==2){
                start=interval.first;
            }
            cnt-=1;
        }
        else {
            if(cnt==1){
                new_merged_intervals.push_back({start, interval.first});
            }
            cnt-=1;
        }
    }
    return new_merged_intervals;
}

int main() {
    
   // Example covering all the cases
   vector<pair<int, int>>meetings = {{1, 5}, {8, 12}, {17, 22}, {24, 26}};
   vector<pair<int, int>>dhd = {{3, 6}, {7, 9}, {18, 21}, {23, 27}};
    
     meetings = merge_intervals(meetings);
        dhd      = merge_intervals(dhd);
    
    //0 => dhd start
    //1 => meetings start
    // 2 => meetings end
    // 3 => dhd end
    vector<pair<int, int>> merged_intervals = merge_intervals_dhd(meetings, dhd);
    
    for(auto intervals: merged_intervals){
        cout<<intervals.first<<" "<<intervals.second<<"\n";
    }
}
