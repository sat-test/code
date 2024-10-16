/*
https://www.interviewbit.com/problems/next-smallest-palindrome/

Next Smallest Palindrome!

*/


string generateString(string str, int n, int m) {
    string rev = "";
    if (n % 2 == 0) {
        rev = str;
        reverse(rev.begin(), rev.end());
        return str + rev;
    } else {
        rev = str.substr(0, m-1);
        reverse(rev.begin(), rev.end());
        return str + rev;
    }
}

string Solution::solve(string A) {
    int n = A.size();
    int m = (n + 1) / 2;
    string str = A.substr(0, m);  // Taking the left half (or half + middle character)

    // Try generating palindrome by incrementing digits from the middle to left
    for (int i = m - 1; i >= 0; i--) {
        for (char ch = A[i] + 1; ch <= '9'; ch++) {  // Start from next lexicographic digit
            str[i] = ch;
            string newStr = generateString(str, n, m);  // Generate a new palindrome
            if (newStr > A) {
                return newStr;
            }
        }
        // Reset the current position to '0' and propagate carry to left side
        str[i] = '0';
    }

    // If no valid palindrome found, this means the input was all 9's like "999", so return "100...001"
    str = "1";
    for (int i = 1; i < n; i++) {
        str += "0";
    }
    str += "1";
    return str;
}
