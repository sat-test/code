/*
Mobile Pattern Lock.

Interviewer introduced himself (Principal SDE) and asked me to introduce myself, which took 10 mins. He didn't pasted the question, but explained to me verbally. There is an n * n grid similar to a mobile lock screen where you swipe in a pattern to unlock the mobile. We need to find how many such patterns are possible with some given constraints.

https://www.naukri.com/code360/problems/mobile-pattern-lock_1263698?leftPanelTabValue=PROBLEM
https://leetcode.com/discuss/interview-experience/5917660/Google-India-or-SWE-L3-or-Interview-Experience.
*/

#include <bits/stdc++.h> 

int calculate(vector<vector<int>> jumps, int visitMask, int curr, int remPattern, unordered_map<string, int>& memo) {
	if(remPattern <= 0) {
		return remPattern == 0 ? 1 : 0;
	}

	string key = to_string(curr) + "_" + to_string(remPattern) + "_" + to_string(visitMask);
	if(memo.find(key) != memo.end()) {
		return memo[key];
	}

    int ways = 0;
	visitMask |= 1<<curr;

	for(int i=1; i< 10; i++) {
		if(!(visitMask & (1<<i)) && (!jumps[i][curr] || (visitMask & ( 1 << jumps[i][curr])))) {
			ways += calculate(jumps, visitMask, i, remPattern-1, memo);
		}
	}

	visitMask &= ~(1 << curr);
	return memo[key] = ways;
}

int numberOfPatterns(int m, int n) {
	vector<vector<int>> jumps(10, vector<int>(10, 0));
	jumps[1][3] = jumps[3][1] = 2;
	jumps[7][9] = jumps[9][7] = 8;
	jumps[1][7] = jumps[7][1] = 4;
	jumps[3][9] = jumps[9][3] = 6;
	jumps[1][9] = jumps[9][1] = jumps[3][7] = jumps[7][3] = jumps[4][6] = jumps[6][4] = jumps[2][8] = jumps[8][2] = 5;

	unordered_map<string, int> memo;
	int res = 0;
	for(int i=m; i<=n; i++) {
		int startFromOne = 4*calculate(jumps, 0, 1, i-1, memo);
		int startFromTwo = 4*calculate(jumps, 0, 2, i-1, memo);
		int startFromFive = calculate(jumps, 0, 5, i-1, memo);
        // cout<<startFromOne<<" "<<startFromTwo<<" "<<startFromFive<<"\n";
		res += (startFromOne + startFromTwo + startFromFive);
	}
	return res;
}
