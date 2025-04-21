/*
You are given a string s, and you have to count the total number of unique substring, where the substring have the same number of frequency of each unique character in that substring. Also the given string can have only digits from '0' to '9'.

Ex 1:
given stirng s = "1212"
answer is 5 : "1", "2", "12", "21" & "1212".

As "12" have each unique char 1 and 2 have frequency 1 and similarly in "1212" we have unique chars 1 and 2 with each having frequency of 2
Here "121" is not valid substring as the frequency of 1 and 2 are not equal.

Ex 2:
s = "11202"
answer is 8 : "1", "2", "0", "11", "12", "20", "02", "120"
here "2" and "02" will be considered as different string.
*/

bool isValid(vector<int> vec) {
    int n = vec.size(), curr = 0;
    for(int i=0; i<n; i++) {
        if(vec[i] == 0) {
            continue;
        } else if(curr == 0) {
            curr = vec[i];
        } else if(curr != vec[i]) {
            return false;
        }
    }
    return true;
}

int solve(string str) {
    int n = str.size(), res = 0;
    unordered_set<string> s;
    for(int i=0; i<n; i++) {
        vector<int> freq(10, 0);
        string curr = "";
        for(int j=i; j<n; j++) {
            ++freq[str[j] - '0'];
            curr += str[j];
            if(isValid(freq) && (s.find(curr) == s.end())) {
                s.insert(curr);
                ++res;
            }
        }
    }
    return res;
}

int main() {
    string str1 = "1212";
    cout<<solve(str1)<<"\n";
    string str2 = "11202";
    cout<<solve(str2)<<"\n";
}
