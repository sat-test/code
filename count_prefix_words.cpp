/*

https://leetcode.com/discuss/interview-question/5604226/Google-phone-Screen-L4-Interview

The interview started with the interviewer introducing himself on Google Meet. The interview began when I opened the interview document.

Sample Input
array = ["bomb", "book", "g","gift", "go", "goal", "goat", "gum","xray","yellow","zebra"]
prefix = "go"
Sample Output
3
Problem Statement
Given the sorted array and prefix, return the number of elements in the array that start with the prefix value. I started by giving a linear approach which takes O(n * k) time complexity (n - length of array, k - length of prefix).

*/

int leftBinraySearch(vector<string> &vec, string &str) {
    int low = 0;
    int high = vec.size();
    int res = -1;
    
    while(low < high) {
        int mid = low + (high-low)/2;
        string s = vec[mid].substr(0, str.size());
        if(s == str) {
            res = mid;
            high = mid;
        } else if(s < str) {
            low = mid+1;
        } else {
            high = mid;
        }
    }
    
    return res;
}

int rightBinraySearch(vector<string> &vec, string &str) {
    int low = 0;
    int high = vec.size();
    int res = -1;
    
    while(low < high) {
        int mid = low + (high-low)/2;
        string s = vec[mid].substr(0, str.size());
        if(s == str) {
            res = mid;
            low = mid+1;
        } else if(s < str) {
            low = mid+1;
        } else {
            high = mid;
        }
    }
    
    return res;
}

int binarySearch(vector<string> &vec, string &str) {
    int i = leftBinraySearch(vec, str);
    int j = rightBinraySearch(vec, str);
    if(i == -1) {
        return 0;
    }
    return j-i+1;
}


int main() {
    vector<string> A = {"bomb", "book", "g","gift", "go", "goal", "goat", "gum","xray","yellow","zebra"};
    string prefix = "go";
    int res = binarySearch(A, prefix);
    cout<<res<<"\n";
}
