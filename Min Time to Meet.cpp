/*
I appeared in uber interview recently and was asked below quastion in the first round.

There are n cars on x axis. i-th Car's initial position is denoted by location[i] and maximum speed by speed[i]. cars can travel in both directions(left and right).
At the end, all cars need to meet at the same location, what would be the minimum time required at which all cars can meet.

Test case
cars : 3
position: [1, 3, 7]
speed: [2, 1, 1]

Answer: 2
https://leetcode.com/discuss/post/6801527/uber-interview-experience-by-kamal14-hwfp/



Solution:
I'll help you solve this problem step by step.
The key insight is that we need to find the optimal meeting point that minimizes the maximum time any car takes to reach it. This is a classic minimax optimization problem.
Let me analyze the approach:

For any meeting point x, each car i will take |location[i] - x| / speed[i] time to reach it
We want to minimize the maximum of all these times
We can use ternary search since the function is unimodal (has a single minimum)

The solution uses ternary search to find the optimal meeting point. Here's why this approach works:
Key Insights:

For any meeting point x, the time for car i to reach it is |location[i] - x| / speed[i]
We want to minimize the maximum time among all cars
The function f(x) = max(|location[i] - x| / speed[i]) is unimodal - it has exactly one minimum

Algorithm:

Set search range from minimum to maximum car position
Use ternary search to find the optimal meeting point
At each iteration, compare function values at two points that divide the range into three parts
Eliminate the part that can't contain the minimum

Verification for your test case:

Cars at positions [1, 3, 7] with speeds [2, 1, 1]
At meeting point x = 5:

Car 1: |1-5|/2 = 2 time units
Car 2: |3-5|/1 = 2 time units
Car 3: |7-5|/1 = 2 time units


Maximum time = 2 ✓

The algorithm efficiently finds this optimal point through ternary search rather than checking all possible positions.
Time Complexity: O(n × log(range/ε)) where ε is the precision
Space Complexity: O(1)
*/  


class Solution {
private:
    double getMaxTime(vector<int> &loc, vector<int> &speed, double x) {
        double maxTime = 0;
        for(int i=0; i<loc.size(); i++) {
            double time = abs(loc[i]-x) / speed[i];
            maxTime = max(maxTime, time);
        }
        return maxTime;
    }
    
public:
    double getMinTimeToMeet(vector<int> &loc, vector<int> speed) {
        double left = *min_element(loc.begin(), loc.end());
        double right = *max_element(loc.begin(), loc.end());
        double EPS = 1e-9;
        while(right - left > EPS) {
            double mid1 = left + (right-left) / 3.0;
            double mid2 = right - (right-left) / 3.0;
            
            double time1 = getMaxTime(loc, speed, mid1);
            double time2 = getMaxTime(loc, speed, mid2);
            
            if(time1 > time2) {
                left = mid1;
            } else {
                right = mid2;
            }
        }
        
        return getMaxTime(loc, speed, (left+right)/2.0);
    }
};

int main() {
    Solution s;
    vector<int> loc = {0, 10, 20, 30};
    vector<int> speed = {1, 2, 3, 4};
    cout<<s.getMinTimeToMeet(loc, speed)<<"\n";
}


//Other Solution
/*

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to calculate maximum time for all cars to reach meeting point x
    double getMaxTime(vector<int>& location, vector<int>& speed, double x) {
        double maxTime = 0.0;
        for (int i = 0; i < location.size(); i++) {
            double time = abs(location[i] - x) / speed[i];
            maxTime = max(maxTime, time);
        }
        return maxTime;
    }
    
    double getMinTimeToMeet(vector<int>& location, vector<int>& speed) {
        // Find the range for ternary search
        double left = *min_element(location.begin(), location.end());
        double right = *max_element(location.begin(), location.end());
        
        // Ternary search to find optimal meeting point
        const double EPS = 1e-9;
        while (right - left > EPS) {
            double mid1 = left + (right - left) / 3.0;
            double mid2 = right - (right - left) / 3.0;
            
            double time1 = getMaxTime(location, speed, mid1);
            double time2 = getMaxTime(location, speed, mid2);
            
            if (time1 > time2) {
                left = mid1;
            } else {
                right = mid2;
            }
        }
        
        // Return the minimum time
        return getMaxTime(location, speed, (left + right) / 2.0);
    }
};

int main() {
    Solution sol;
    
    // Test case from the problem
    vector<int> location = {1, 3, 7};
    vector<int> speed = {2, 1, 1};
    
    double result = sol.getMinTimeToMeet(location, speed);
    
    cout << "Minimum time for all cars to meet: " << result << endl;
    
    // Let's verify by checking the meeting point around x = 5
    cout << "\nVerification:" << endl;
    for (double x = 4.5; x <= 5.5; x += 0.1) {
        double maxTime = sol.getMaxTime(location, speed, x);
        cout << "Meeting point x = " << x << ", Max time = " << maxTime << endl;
    }
    
    // Additional test cases
    cout << "\n--- Additional Test Cases ---" << endl;
    
    // Test case 2: Cars at same position
    vector<int> loc2 = {5, 5, 5};
    vector<int> speed2 = {1, 2, 3};
    cout << "Test 2 - Same position: " << sol.getMinTimeToMeet(loc2, speed2) << endl;
    
    // Test case 3: Two cars
    vector<int> loc3 = {0, 10};
    vector<int> speed3 = {1, 1};
    cout << "Test 3 - Two cars: " << sol.getMinTimeToMeet(loc3, speed3) << endl;
    
    return 0;
}

/*
Explanation of the algorithm:

1. We use ternary search because the function f(x) = max(|location[i] - x| / speed[i]) 
   is unimodal (has exactly one minimum).

2. For the given test case:
   - Car 1: position 1, speed 2
   - Car 2: position 3, speed 1  
   - Car 3: position 7, speed 1
   
   At meeting point x = 5:
   - Car 1 takes |1-5|/2 = 4/2 = 2 time units
   - Car 2 takes |3-5|/1 = 2/1 = 2 time units
   - Car 3 takes |7-5|/1 = 2/1 = 2 time units
   
   Maximum time = 2, which matches the expected answer.

Time Complexity: O(n * log(range/epsilon)) where range is the difference between 
max and min positions, and epsilon is our precision.

Space Complexity: O(1)
*/

*/
