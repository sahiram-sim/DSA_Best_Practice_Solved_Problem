#include <bits/stdc++.h>
using namespace std;

string str;
int n;
int dp[20][2];

int rec(int idx, int tight)
{
    if (idx == str.size())
        return 1;
    if (dp[idx][tight])
        return dp[idx][tight];

    int ans = 0;
    int limit = tight ? str[idx] - '0' : 9;
    for (int i = 0; i <= limit; i++)
    {
        ans += rec(idx + 1, (tight && (i == limit)));
    }
    return dp[idx][tight] = ans;
}

int solve(int num)
{
    str = to_string(num);
    n = str.size();

    rec(0, 1);
}

int main()
{
    int num;
    cin >> num;

    cout << solve(num) << endl;
}