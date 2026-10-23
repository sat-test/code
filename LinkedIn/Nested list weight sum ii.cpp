/*
Given a nested list of integers nestedList. Each element is either an integer or a list whose elements may also be integers or other lists. The depth of an integer is the number of lists that it is inside of. For example, the nested list [1,[2,2],[[3],2],1] has each integer's value set to its depth.

Let maxDepth be the maximum depth of any integer. The weight of an integer is maxDepth - (the depth of the integer) + 1.

Your task is to find the sum of each integer in nestedList multiplied by its weight.

Examples:

Input: nestedList = [[1, 1], 2, [1, 1]] 
Output:  8
Explanation: Four 1's with a weight of 1, one 2 with a weight of 2. 1*1 + 1*1 + 2*2 + 1*1 + 1*1 = 8



Input: nestedList = [1, [3, [5]]]
Output:  14
Explanation: One 1 at depth 3, one 3 at depth 2, and one 5 at depth 1; 1*3 + 3*2 + 5*1 = 14) 

*/

#include <bits/stdc++.h>
using namespace std;

class MyNestedInteger {
    bool isInt;
    int value;
    vector<MyNestedInteger> children;

public:
    MyNestedInteger(int x) : isInt(true), value(x) {}

    MyNestedInteger(vector<MyNestedInteger> list)
        : isInt(false), value(0), children(move(list)) {}

    static MyNestedInteger makeList(vector<MyNestedInteger> list) {
        return MyNestedInteger(move(list));
    }

    bool isInteger() const {
        return isInt;
    }

    int getInteger() const {
        return value;
    }

    const vector<MyNestedInteger>& getList() const {
        return children;
    }
};

class Solution {
public:
    // Implement this function
    int depthSumInverse(vector<MyNestedInteger>& nestedList) {
        unordered_map<int, int> m;
        int depth = 1, maxDepth = 0;
        queue<MyNestedInteger> q;
        
        for (const auto& ni : nestedList) {
            q.push(ni);
        }
        
        while(!q.empty()) {
            int s = q.size();
            for(int i=0; i<s; i++) {
                MyNestedInteger nI = q.front();
                q.pop();
                if(nI.isInteger()) {
                    m[depth] += nI.getInteger();
                    maxDepth = max(maxDepth, depth);
                } else {
                    for(MyNestedInteger child: nI.getList()) {
                        q.push(child);
                    }
                }
            }
            ++depth;
        }
        
        int sum = 0;
        for(auto it: m) {
            sum += (maxDepth - it.first + 1) * it.second;
        }
        return sum;
    }
};

// Add test cases and a test harness here to run locally.
int main() {
    Solution solution;

    // Test case 1: [[1,1],2,[1,1]]
    vector<MyNestedInteger> test1 = {
        MyNestedInteger::makeList({
            MyNestedInteger(1),
            MyNestedInteger(1)
        }),
        MyNestedInteger(2),
        MyNestedInteger::makeList({
            MyNestedInteger(1),
            MyNestedInteger(1)
        })
    };
    cout << solution.depthSumInverse(test1) << " | Expected: 8\n";

    // Test case 2: [1,[3,[5]]]
    vector<MyNestedInteger> test2 = {
        MyNestedInteger(1),
        MyNestedInteger::makeList({
            MyNestedInteger(3),
            MyNestedInteger::makeList({
                MyNestedInteger(5)
            })
        })
    };
    cout << solution.depthSumInverse(test2) << " | Expected: 14\n";

    // Test case 3: [6]
    vector<MyNestedInteger> test3 = {
        MyNestedInteger(6)
    };
    cout << solution.depthSumInverse(test3) << " | Expected: 6\n";

    // Test case 4: [[],[1,[2]]]
    vector<MyNestedInteger> test4 = {
        MyNestedInteger::makeList({}),
        MyNestedInteger::makeList({
            MyNestedInteger(1),
            MyNestedInteger::makeList({
                MyNestedInteger(2)
            })
        })
    };
    cout << solution.depthSumInverse(test4) << " | Expected: 4\n";

    // Test case 5: [-1,[-2,[-3]]]
    vector<MyNestedInteger> test5 = {
        MyNestedInteger(-1),
        MyNestedInteger::makeList({
            MyNestedInteger(-2),
            MyNestedInteger::makeList({
                MyNestedInteger(-3)
            })
        })
    };
    cout << solution.depthSumInverse(test5) << " | Expected: -10\n";

    return 0;
}
