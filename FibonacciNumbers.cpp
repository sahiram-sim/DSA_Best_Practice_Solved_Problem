// https://cses.fi/problemset/task/1722/
// The Fibonacci numbers can be defined as follows:
// F_0=0
// F_1=1
// F_n = F_{n-2}+F_{n-1}
// Your task is to calculate the value of F_n for a given n.
// Input
// The only input line has an integer n.
// Output
// Print the value of F_n modulo 10^9+7.
// Constraints
// 0 <= n <= 10^18
// Example
// Input:
// 10
// Output:
// 55

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;

const long long MOD = 1e9 + 7;

#define rep(i,n) for(int i=0; i < n; i++)

class Matrix
{
public:
    vvi mat;
    int n, m;
    Matrix(int n, int m) : n(n), m(m) { mat.assign(n, vi(m, 0)); }
};

Matrix multiPly(Matrix a, Matrix b)
{
    Matrix res(a.m, b.n);
    rep(i, a.n) rep(j, b.m) rep(k, a.m) res.mat[i][j] = (res.mat[i][j] + 1LL * a.mat[i][k] * b.mat[k][j]) % MOD;
    return res;
}

Matrix power(Matrix a, ll exp)
{
    Matrix res(a.n, a.m);
    rep(i, a.n) res.mat[i][i] = 1;
    while (exp)
    {
        if (exp & 1)
            res = multiPly(res, a);
        a = multiPly(a, a);
        exp >>= 1;
    }
    return res;
}

int main()
{
    ll n;
    cin >> n;
    if (n == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    Matrix c(2, 2);
    c.mat = {{1, 1}, {1, 0}};

    Matrix T = power(c, n - 1);
    cout << T.mat[0][0] % MOD << endl;
}
