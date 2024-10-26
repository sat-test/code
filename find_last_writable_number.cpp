/*
https://leetcode.com/discuss/interview-question/5966234/Google-Bangalore-Experience-or-L4

 You are tasked with writing a sequence of positive integers starting from 1. However, you have a constraint: for each digit (0-9), you can press its corresponding key a maximum of n times, where n can be as large as a 64-bit integer. You need to determine the last number you can write before running out of allowed presses for any digit.

Example:
For n = 5, the last number you can write is 12. You can write numbers from 1 to 12, but to write 13, you would need to press the '1' key for the sixth time, which exceeds the limit.
*/

#include <iostream>

using namespace std;

// Function to count occurrences of the digit '1' from 1 to a given number 'num'
long long countOnes(long long num) {
    long long count = 0;
    long long factor = 1;  // We start with the units place

    while (factor <= num) {
        long long lower = num - (num / factor) * factor;    // Digits to the right of current position
        long long current = (num / factor) % 10;            // Current digit
        long long higher = num / (factor * 10);             // Digits to the left of current position

        if (current == 0) {
            count += higher * factor;
        } else if (current == 1) {
            count += higher * factor + lower + 1;
        } else {
            count += (higher + 1) * factor;
        }

        factor *= 10;
    }
    return count;
}

long long findLastWritableNumber(long long n) {
    long long low = 1, high = 1e18, result = 1;

    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (countOnes(mid) <= n) {
            result = mid;       // Mid is valid, try for a larger number
            low = mid + 1;
        } else {
            high = mid - 1;     // Mid is too large, try smaller
        }
    }

    return result;
}

int main() {
    long long n;
    cout << "Enter maximum presses allowed per digit (n): ";
    cin >> n;

    long long lastWritableNumber = findLastWritableNumber(50000);
    cout << "The last number you can write is: " << lastWritableNumber << endl;

    return 0;
}
