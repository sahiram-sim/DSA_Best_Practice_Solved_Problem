#include <bits/stdc++.h>
using namespace std;

// count the numbers with digit sum = k;
int dp[20][200][2];
int n, N, K;
string str;

int rec(int idx, int sum, int tight)
{
    if(sum > K) return 0;
    if (idx == n) return (sum == K);
    if(dp[idx][sum][tight] !=-1) return dp[idx][sum][tight];
    int cnt = 0;
    int limit = tight?str[idx]-'0':9;
    for(int i=0;i<=limit;i++){
        cnt+=rec(idx+1, sum+i, tight&&(i==limit));
    }
    return dp[idx][sum][tight] = cnt;
}

int main()
{
    cin >> N >> K;
    str = to_string(N);
    n = str.size();
    memset(dp, -1, sizeof(dp));
    cout<<"Here is the count: "<< rec(0, 0, 1)<<endl;
}