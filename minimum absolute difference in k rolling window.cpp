/*
Question: Given a size N array, for every K sized rolling window in the array, find the minimum absolute difference between any two elements in the K sized window.
https://leetcode.com/discuss/interview-experience/5655907/Uber-or-SDE-2-or-Bangalore-or-July-2024-Offer
*/

int solve(vector<int> A, int k) {
    set<int> s;
    int res = INT_MAX;
    s.insert(A[0]);
    for(int i=1; i<A.size(); i++) {
        s.insert(A[i]);
        if(s.size() > k) {
            s.erase(A[i-k]);
        }
        auto it  = s.find(A[i]);
        int prevVal = INT_MAX, nextVal = INT_MAX;
        if(it != s.begin()) {
            prevVal = *(prev(it));
        }
        auto itNext = next(it);
        if(itNext != s.end()) {
            nextVal = *itNext;
        }
        res = min(res, min(abs(A[i]-prevVal), abs(nextVal-A[i])));
    }
    return res;
}

int main() {
    vector<int> A = {3, 25, 8, 19, 36, 15, 100, 9};
    int k = 4;
    int res = solve(A, k);
    cout<<res<<"\n";
}
