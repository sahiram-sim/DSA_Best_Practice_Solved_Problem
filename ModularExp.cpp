#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
const int MOD = 1e9 + 7;

long long fact[MAXN + 1], invFact[MAXN + 1];

long long myPow(long long a, long long b, long long m = MOD)
{
    long long res = 1;
    while (b)
    {
        if (b & 1)
            res = ((res % m) * (a)) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

void preProcessing()
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invFact[MAXN] = myPow(fact[MAXN], MOD - 2, MOD);
    for (int i = MAXN - 1; i >= 0; i--)
    {
        invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }
}

long long nCr(int n, int r)
{
    if (n < 0 || r < 0 || n < r)
        return 0;
    return (fact[n] * invFact[r] % MOD) * (invFact[n - r] % MOD) % MOD;
}

void showData()
{
    cout << "Here are the fact\n";
    for (int i = 0; i <= MAXN; i++)
        cout << fact[i] << " ";
    cout << "\nHere are the inv fact\n";
    for (int i = 0; i <= MAXN; i++)
        cout << invFact[i] << " ";
    cout << endl;
}

int main()
{
    long long a, b;
    cin >> a >> b;

    preProcessing();
    cout << myPow(a, b) << endl;
    showData();
    cout << nCr(5, 2) << endl;
}