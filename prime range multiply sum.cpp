/*
https://leetcode.com/discuss/interview-question/5854983/Uber-OA

You have N ranges where the i-th range is from low[i] to high[i].
You need to create an array brr of length N. However, brr[i] can only be any prime number such that low[i] <= brr[i] <= high[i] for all possible i.

As we know there can be multiple ways to create brr. It is given that the score of an array is the multiplication of all values in it.

Your task is to find the sum of the score of all possible unique permutations of brr. Since the answer can be very large, return the answer modulo 10^9+7.

Note:

It is guaranteed that there will be at least one element in brr[i], which means there will always be a prime number between low[i] and high[i].
low[i] <= high[i] for all possible i (1 <= i <= N).

constraints

1<=N<=10^5
1<=low,high<=10^6

Sample Input 3

2
1
3
3
5
Sample Output 3
40

*/

vector<int> primeNumbers() {
    int N = 1000000;
    vector<bool> A(N+1, true);
    A[0] = false;
    A[1] = false;
    vector<int> prime;
    for(int i=2; i*i<=N; i++) {
        if(A[i] == true) {
            for(int j=i*i; j<=N; j+=i) {
                A[j] = false;
            }
        }
    }
    for(int i=2; i<=N; i++) {
        if(A[i] == true) {
            prime.push_back(i);
        }
    }
    return prime;
}

vector<long long> prefixSum(vector<int> nums) {
    int N = nums.size();
    vector<long long> sum(N, 0);
    sum[0] = nums[0];
    for(int i=1; i<N; i++) {
        sum[i] = sum[i-1] + nums[i];
    }
    return sum;
}

int findSum(int low, int high, vector<int> prime, vector<long long> primeSum) {
    int lowInd = lower_bound(prime.begin(), prime.end(), low) - prime.begin();
    int highInd = upper_bound(prime.begin(), prime.end(), high) - prime.begin() - 1;
    if(lowInd > highInd) return 0;
    if(lowInd == 0) {
        return primeSum[highInd];
    }
    return primeSum[highInd] - primeSum[lowInd-1];
}

long long solve(vector<int> low, vector<int> high, int N) {
    int M = 1000000007;
    vector<int> prime = primeNumbers();
    vector<long long> primeSum = prefixSum(prime);
    long long res = 1;
    for(int i=0; i<N; i++) {
        long long sumOfPrimes = findSum(low[i], high[i], prime, primeSum);
        res = (res * sumOfPrimes) % M;
    }
    return res;
}


int main() {
    int N = 2;
    vector<int> low = {1, 3};
    vector<int> high = {3, 5};
    long long res = solve(low, high, N);
    cout<<res<<"\n";
}
