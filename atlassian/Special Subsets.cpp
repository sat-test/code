/*
Question 2 — Special Subsets
You are given an integer array a of size n.
Consider any subset S of indices from {0, 1, ..., n-1}. Let T be the set of indices that are not included in S.
A subset S is called special if:
\[
\text{sum}(S) \ge a[j] \quad \text{for every } j \in T
\]
In other words, the sum of the elements selected in S must be greater than or equal to every element that is not selected.
Task 1
Count the total number of special subsets.
Follow-Up 1
Instead of only counting the special subsets, calculate:
\[
\sum_{\text{special } S} \text{sum}(S)
\]
That is, find the sum of the sums of all special subsets.
Follow-Up 2
Calculate:
\[
\sum_{\text{special } S} \text{product}(S)
\]
That is, find the sum of the products of the elements in all special subsets.
Return all answers modulo:
\[
10^9 + 7
\]
Example
a = [1, 2, 3]

For subset S = {1, 2}:
sum(S) = 2 + 3 = 5

The only unselected element is 1, and:
5 >= 1

Therefore, {1, 2} is a special subset.
Similarly, {2, 3} and {1, 2, 3} are special subsets.
Important: The condition applies only to the elements not selected in S.
*/
class Solution {
public:
    static const int MOD = 1e9 + 7;
    int countSpecialSubsets(vector<int> &A) {
        int n = A.size();
        
        sort(A.begin(), A.end());
        int maxi = A[n-1];
        
        vector<long long> dp(maxi, 0);
        dp[0] = 1;
        
        for(int i=0; i<n-1; i++) {
            int x = A[i];
            for(int sum = maxi - 1; sum >= x; sum--) {
                dp[sum] = (dp[sum] + dp[sum-x]) % MOD;
            }
        }
        
        long long nonSpecial = 0;
        for(int sum = 1; sum < maxi; sum++) {
            nonSpecial = (nonSpecial + dp[sum]) % MOD;
        }
        
        long long total = (modPow(2, n) - 2 + MOD) % MOD;
        
        return (total - nonSpecial + MOD) % MOD;
    } 
private:
    long long modPow(long long base, int exp) {
        long long res = 1;
        while(exp > 0) {
            if(exp & 1) {
                res  = res * base % MOD;
            }
            base = base * base % MOD;
            exp >>= 1;
        }
        
        return res;
    }
};

// int main() {
//     Solution s;
//     vector<int> vec = {2, 5, 3, 7};
//     cout<<s.countSpecialSubsets(vec)<<"\n";
// }

// class Solution {
// public:
//     static const int MOD = 1e9 + 7;

//     long long sumOfSpecialSubsets(vector<int>& A) {
//         int n = A.size();

//         sort(A.begin(), A.end());

//         int maxi = A[n - 1];

//         // count[s] = number of subsets with sum s
//         // sum[s]   = sum of sums of those subsets
//         vector<long long> count(maxi, 0);
//         vector<long long> sum(maxi, 0);

//         // Empty subset
//         count[0] = 1;

//         for (int i = 0; i < n - 1; i++) {
//             int x = A[i];

//             for (int s = maxi - 1; s >= x; s--) {

//                 // Subsets from previous state having sum (s - x)
//                 long long oldCount = count[s - x];
//                 long long oldSum = sum[s - x];

//                 // Number of new subsets
//                 count[s] = (count[s] + oldCount) % MOD;

//                 // Their new sum becomes:
//                 // old subset sum + x
//                 //
//                 // If there are oldCount subsets:
//                 // oldSum + x * oldCount
//                 sum[s] = (sum[s] + oldSum + x * oldCount) % MOD;
//             }
//         }

//         /*
//          * Non-special subsets:
//          * They don't contain maxi and have sum < maxi.
//          *
//          * We need their SUM OF SUMS.
//          */
//         long long nonSpecialSum = 0;

//         for (int s = 1; s < maxi; s++) {
//             nonSpecialSum =
//                 (nonSpecialSum + sum[s]) % MOD;
//         }

//         /*
//          * Now calculate sum of sums of ALL
//          * non-empty proper subsets.
//          *
//          * Each element appears in exactly 2^(n-1) subsets.
//          *
//          * Therefore:
//          *
//          * total sum =
//          * (sum of all elements) * 2^(n-1)
//          *
//          * But we must exclude the full array.
//          */
//         long long totalElementSum = 0;

//         for (int x : A) {
//             totalElementSum =
//                 (totalElementSum + x) % MOD;
//         }

//         long long total =
//             totalElementSum * modPow(2, n - 1) % MOD;

//         // Remove the full array's sum
//         total =
//             (total - totalElementSum + MOD) % MOD;

//         /*
//          * Special subsets =
//          * all proper non-empty subsets
//          * - non-special subsets
//          */
//         return (total - nonSpecialSum + MOD) % MOD;
//     }

// private:
//     long long modPow(long long base, int exp) {
//         long long res = 1;

//         while (exp > 0) {
//             if (exp & 1) {
//                 res = res * base % MOD;
//             }

//             base = base * base % MOD;
//             exp >>= 1;
//         }

//         return res;
//     }
// };


// class Solution {
// public:
//     static const int MOD = 1e9 + 7;

//     long long sumOfProductOfSpecialSubsets(vector<int>& A) {
//         int n = A.size();

//         sort(A.begin(), A.end());

//         int maxi = A[n - 1];

//         // count[s]   = number of subsets having sum s
//         // product[s] = sum of products of those subsets
//         vector<long long> count(maxi, 0);
//         vector<long long> product(maxi, 0);

//         // Empty subset
//         // Its product is considered 1.
//         count[0] = 1;
//         product[0] = 1;

//         for (int i = 0; i < n - 1; i++) {
//             int x = A[i];

//             for (int s = maxi - 1; s >= x; s--) {

//                 long long oldCount = count[s - x];
//                 long long oldProduct = product[s - x];

//                 // Add subsets formed without x
//                 // and subsets formed by adding x.

//                 count[s] =
//                     (count[s] + oldCount) % MOD;

//                 product[s] =
//                     (product[s] + oldProduct * x) % MOD;
//             }
//         }

//         /*
//          * Non-special subsets:
//          *
//          * They don't contain maxi
//          * and their sum < maxi.
//          *
//          * Therefore calculate the sum of products
//          * for all sums < maxi.
//          *
//          * Ignore sum = 0 because that represents
//          * the empty subset.
//          */
//         long long nonSpecialProduct = 0;

//         for (int s = 1; s < maxi; s++) {
//             nonSpecialProduct =
//                 (nonSpecialProduct + product[s]) % MOD;
//         }

//         /*
//          * Calculate product sum of ALL
//          * non-empty proper subsets.
//          *
//          * For every element x:
//          *
//          *   either don't select x -> 1
//          *   select x             -> x
//          *
//          * Therefore:
//          *
//          * product(1 + A[i])
//          *
//          * gives the sum of products of ALL subsets,
//          * including the empty subset.
//          *
//          * Remove:
//          * 1             -> empty subset
//          * product(A)    -> full array
//          */

//         long long total = 1;
//         long long fullProduct = 1;

//         for (int x : A) {
//             total = total * (x + 1) % MOD;
//             fullProduct = fullProduct * x % MOD;
//         }

//         // Remove empty subset
//         total = (total - 1 + MOD) % MOD;

//         // Remove full array
//         total = (total - fullProduct + MOD) % MOD;

//         /*
//          * Special subsets =
//          * all proper non-empty subsets
//          * - non-special subsets
//          */
//         return (total - nonSpecialProduct + MOD) % MOD;
//     }
// };
