/*
Problem statement
You have been given ‘N’ houses, each house can be painted with any of three colours: green, red and yellow. You are also given a “cost” matrix of ‘N’ * 3 dimension which represents the cost of painting an i-th house (0-th based indexing) with j-th colour. The colour code is as follows: green - 0, red - 1 and yellow - 2. Now, you are supposed to find the minimum cost of painting all houses such that no adjacent houses are painted with the same colour.

Detailed explanation ( Input/output format, Notes, Images )
Constraints :
1 <= T <= 50
1 <= N <= 10000
0 <= cost[i][j] <= 100

Where cost[i][j] represents the cost of painting the i-th house with j-th colour.

Time limit: 1 sec
Sample Input 1 :
2
2
2 3 2
1 4 1
1
1 2 3
Sample output 1 :
3
1
Explanation Of Sample Output 1 :
For the first test case, in the optimal case, we can paint house 0 (0-th based indexing) with colour 0 (0-th based indexing) and house 1 with colour 2. The cost will be 2 + 1 = 3.

For the second test case, we can choose the colour 0 to paint the house. And the cost will be 1.
Sample Input 2 :
2
3
14 2 11
11 14 5
14 3 10
2
1 2 3
1 4 6
Sample output 2 :
10
3
Explanation Of Sample Output 2 :
For the first test case, in the optimal case, we can paint house 0 (0-th based indexing) with colour 1 (0-th based indexing), house 1 with colour 2  and house 2 with colour 1. The cost will be 2 + 5 + 3 = 10.

For the second test case, the minimum cost will be 3.
*/

int minCost(vector<vector<int>> &cost) {
	int green = 0, red = 0, yellow = 0;
	int prevGreen, prevRed, prevYellow;

	for(auto c: cost) {
		prevGreen = green;
		prevRed = red;
		prevYellow = yellow;
		green = min(prevRed, prevYellow) + c[0];
		red = min(prevGreen, prevYellow) + c[1];
		yellow = min(prevRed, prevGreen) + c[2];
	}

	return min(green, min(red, yellow));	
}
