//https://leetcode.com/discuss/interview-question/5742935/Google-OA-Question-Help-required

#include<bits/stdc++.h>

using namespace std;


void printVec(vector<int>& entries) {
    for(int i=0; i<entries.size(); i++) {
        cout<<entries[i]<<" ";
    }
    cout<<"\n";
}

vector<int> lexicographicallySmallestPermutation(vector<int>& entries) {
    int n = entries.size();
    vector<int> pos(n + 1); 
    for (int i = 0; i < n; ++i) {
        pos[entries[i]] = i+1;
    }
    
    int s = n-1, start = 1;
    for(int i=1; i<=n && s > 0; i++) {
        cout<<i<<"\n";
        int ind = pos[i];
        while(ind > start && s > 0) {
            int pInd = ind-1;
            swap(entries[ind-1], entries[pInd-1]);
            pos[entries[ind-1]] = pInd;
            pos[entries[pInd-1]] = ind;
            --ind;
            --s;
            printVec(entries);
        } 
        ++start;
    }
    
    return entries;
}

int main() {
    vector<int> entries = {2,1,3,5,6,4};  // Example input
    vector<int> result = lexicographicallySmallestPermutation(entries);
    
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
