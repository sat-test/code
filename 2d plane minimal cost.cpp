/*
Given a 2d plane, we are given n cars and their postion coordinates on the 2d plane in the form of an array.

I/P format : X[n] -> x-coordinates of n cars, Y[n] -> y coordinates of n cars

The objective of the problem is to bring all the cars on the same line parallel to the horizontal (x-axis) in 2d plane, with no gap between 2 cars. We are asked to achieve the objective with minimum fuel cost. The fuel cost for moving a car from (x1,y1) to (x2, y2) is
abs(x1-x2) + abs(y1-y2)

Note : no gap between cars mean that if car1 is parked at (x1, y) then the next car should be parked at (x1+1, y)

https://leetcode.com/discuss/interview-question/3621750/Fivetran-SDE-2-Connectors-interview-question
https://freedium.cfd/https://takeitoutamber.medium.com/hackerrank-coding-interview-5-assigned-parking-f74fb68f424f
*/  


int calculateMinCost1(vector<int> x, vector<int> y) {
    int n = x.size();
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    int medianX = x[n/2];
    int medianY = y[n/2];
    int res = 0;
    for(int i=0; i<n; i++) {
        int diffY = abs(y[i] - medianY);
        int diffX = abs(abs(medianX - x[i]) - abs(n/2 - i));
        res += diffX + diffY;
    }
    return res;
}

int calculateMinCost2(vector<int> x, vector<int> y) {
    int n = x.size();
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for(int i=0; i<n; i++) {
        x[i] -= i;
    }
    sort(x.begin(), x.end());
    
    int medianX = x[n/2];
    int medianY = y[n/2];
    int res = 0;
    for(int i=0; i<n; i++) {
        int diffY = abs(y[i] - medianY);
        int diffX = abs(x[i] - medianX);
        res += diffX + diffY;
    }
    return res;
}


int main() {
    vector<int> x = {1, 2, 4, 6, 7};
    vector<int> y = {2, 3, 5, 6, 6};
    cout<<calculateMinCost1(x, y)<<"\n";
    cout<<calculateMinCost2(x, y)<<"\n";
}
