#include <bits/stdc++.h>
using namespace std;

string s;
long long dp[20][2]; // dp[pos][tight]

long long solve(int pos, int tight)
{
    if (pos == s.size())
        return 1; // valid number

    if (dp[pos][tight] != -1)
        return dp[pos][tight];

    int limit = tight ? s[pos] - '0' : 9;
    long long ans = 0;

    for (int d = 0; d <= limit; d++)
    {
        ans += solve(pos + 1, tight && (d == limit));
    }
    return dp[pos][tight] = ans;
}

long long countUpTo(long long n)
{
    s = to_string(n);
    memset(dp, -1, sizeof(dp));
    return solve(0, 1);
}

int main()
{
    long long n;
    cin >> n;
    cout << countUpTo(n) << "\n";
}
