/*

Description
There is a long and thin  painting that can be represented by a number line. You are given a 0-indexed 2D integer array paint of length n, where paint[i] = [starti, endi]. This means that on the ith day you need to paint the area between starti and endi.

 Painting the same area multiple times will create an uneven painting so you only want to paint each area of the painting at most once.

Return an integer array worklog of length n, where worklog[i] is the amount of new area that you painted on the ith day.

Input: paint = [[1,4],[4,7],[5,8]]
Output: [3,3,1]
Explanation:
On day 0, paint everything between 1 and 4.
The amount of new area painted on day 0 is 4 - 1 = 3.
On day 1, paint everything between 4 and 7.
The amount of new area painted on day 1 is 7 - 4 = 3.
On day 2, paint everything between 7 and 8.
Everything between 5 and 7 was already painted on day 1.
The amount of new area painted on day 2 is 8 - 7 = 1.

https://leetcode.ca/2022-02-19-2158-Amount-of-New-Area-Painted-Each-Day/
https://leetcode.com/problems/amount-of-new-area-painted-each-day/
*/


vector<int> amountPainted(vector<vector<int>>& paint) {
    vector<int> line(50001, 0);
    vector<int> res(paint.size(), 0);
    
    for(int i=0; i<paint.size(); i++) {
        int start = paint[i][0], end = paint[i][1];
        while(start < end) {
            if(line[start] == 0) {
                line[start] = end;
                ++res[i];
                ++start;
            } else {
                start = line[start];
            }
        }
    }
    return res;
}


int main() {
    vector<vector<int>> A = {{1,4},{4,7},{5,8}};
    vector<int> res = amountPainted(A);
    for(int r : res) {
        cout<<r<<" ";
    }
    cout<<"\n";
}
