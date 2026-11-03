/*
You are given a positive integer ‘N’. Find all the unique combinations of factors of the given number ‘N’. The product of the factors in each combination should be ‘N’.

You should return a list of combinations of factors. In each combination, factors must be sorted in non-decreasing order. All combinations must be placed in lexicographical order in the list. See the example for more clarity.

Note

1. Factors should be strictly greater than 1 and strictly less than ‘N’.

2. If there is no such possible combination of factors, then return an empty list. 
Example:

Consider the positive integer ‘N’ = 12.
Then, we can observe that -:
12 = 2 * 2 * 3
12 = 2 * 6
12 = 3 * 4

i.e,  possible combinations of factors are [2, 2, 3], [2, 6], [3, 4].
Thus, we should return list [[2,2,3], [2,6], [3, 4]].  Note that in this list all combinations are sorted in non-decreasing order, and all the combinations in the list are placed in the lexicographical order.

*/

#include <bits/stdc++.h> 

void traverse(int n, int start, vector<int> &curr, vector<vector<int>> &res) {
	for(int i=start; i<=n/i; i++) {
		if(n%i != 0) {
			continue;
		}
		curr.push_back(i);
		curr.push_back(n/i);
		res.push_back(curr);
		curr.pop_back();
		traverse(n/i, i, curr, res);
		curr.pop_back();
	}
}

vector<vector<int>> factorCombinations(int n) {
	vector<vector<int>> res;
	vector<int> curr;

	traverse(n, 2, curr, res);
	sort(res.begin(), res.end());
	return res;
}
