/*
https://cses.fi/problemset/task/2430/
https://codeforces.com/blog/entry/117961

Your task is to find a minimum length bit string that has exactly n distinct subsequences.
For example, a correct solution for n=6 is 101 whose distinct subsequences are 0, 1, 01, 10, 11 and 101.
Input
The only input line has an integer n.
Output
Print one bit string: a solution to the task. You can print any valid solution.
Constraints

1 \le n \le 10^6

Example
Input:
6

Output:
101

*/

#include<bits/stdc++.h>
using namespace std;
string trace(int a,int b)
{
    if(a==b)return "";
    else if(a>b)return '1'+trace(a-b,b);
    else return '0'+trace(a,b-a);
}
int trace_len(int a,int b)
{
    if(a==b)return 0;
    else if(a>b)return 1+trace_len(a-b,b);
    else return 1+trace_len(a,b-a);
}
int main()
{
    int n = 6;
    int b,mn=++n;
    for(int a=1;a<=n+1;a++)
    {
        if(__gcd(a,n+1)!=1)continue;
        int len=trace_len(a,n-a+1);
        if(len<mn)mn=len,b=n-a+1;
    }
    cout<<trace(n-b+1,b)<<"\n";
}
