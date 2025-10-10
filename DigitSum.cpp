#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

string K;
int D;
int n;

long long dp[10005][105][2];

long long dfs(int pos, int sum_mod, int tight){
    // Base case: processed all digits
    if (pos == n)
        return (sum_mod == 0) ? 1 : 0;

    long long &res = dp[pos][sum_mod][tight];
    if (res != -1)
        return res;
    res = 0;

    int limit = tight ? (K[pos] - '0') : 9;

    for (int dig = 0; dig <= limit; ++dig){
        res += dfs(pos + 1, (sum_mod + dig) % D, (tight && (dig == limit)));
        if (res >= MOD)
            res -= MOD;
    }

    return res;
}

int main(){
    cin >> K >> D;
    n = K.size();

    memset(dp, -1, sizeof(dp));

    long long ans = dfs(0, 0, 1);
    // exclude 0
    ans = (ans - 1 + MOD) % MOD;

    cout << ans << "\n";
    return 0;
}
