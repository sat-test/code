/*
Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.

Example 1:

Input: points = [[1,1],[2,2],[3,3]]
Output: 3
Example 2:

Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
*/

class Solution {
private:
    pair<int, int> getSlope(vector<int> point1, vector<int> point2) {
        int x1 = point1[0], x2 = point2[0];
        int y1 = point1[1], y2 = point2[1];
        int gcd = __gcd(y2-y1, x2-x1);
        return {(y2-y1)/gcd, (x2-x1)/gcd};
    }

public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), res = 0;
        for(int i=0; i<n; i++) {
            map<pair<int, int>, int> m;
            int same = 1;
            for(int j=i+1; j<n; j++) {
                if(points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    ++same;
                } else {
                    pair<int, int> slope = getSlope(points[i], points[j]);
                    ++m[slope];
                }
            }
            res = max(res, same);
            for(auto it: m) {
                res = max(res, it.second + same);
            }
        }
        return res;
    }
};
