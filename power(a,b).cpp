#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

ll expPow(int a, int b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = ((res % MOD) * (a % MOD)) % MOD;
        a = ((a % MOD) * (a % MOD)) % MOD;
        b >>= 1;
    }
    return (res % MOD);
}

int main()
{
    int a, b;
    cin >> a >> b;
    cout << expPow(a, b) << endl;
}