#include <bits/stdc++.h>
using namespace std;

// ========== Aliases ==========
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using str = string;

// ========== Macros ==========
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define rep(i, n) for (int i = 0; i < n; i++)
#define repp(i, a, b) for (int i = a; i < b; i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define each(x, a) for (auto &x : a)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define pb puch_back
#define eb emplace_back
#define mp make_pair
#define fi first
#define se second
#define sz(x) (int)(x).size()
#define YES cout << "YES\n"
#define NO cout << "NO\n"
#define endl '\n'

// =========== Constants ==========
constexpr int INF = 1e9 + 7;
constexpr ll INF = 4e18;
constexpr int MOD = 1e9 + 7;
constexpr double EPS = 1e-9;

class Matrix
{
    vvl mat;
    int size;
    Matrix(int n) : size(n) { mat.assign(n, vl(n, 0)); }
};

Matrix Multiply(Matrix a, Matrix b)
{
    int n = a.size;
    Matrix c(n);
    rep(i, n)
        rep(j, n)
            rep(k, n)
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
    return c;
}
Matrix power(Matrix base, ll exp)
{
    int n = base.size;
    Matrix res(n);
    rep(i, n) res.mat[i][i] = 1; // identiy Matrix
    while (exp)
    {
        if (exp & 1)
            res = Multiply(res, base);
        base = Multiply(base, base);
        exp >>= 1;
    }
    return res;
}

ll fib(ll n)
{
    if (n == 0)
        return 0;
    Matrix T(n);
    T.m = {{1, 1}, {1, 0}};
    T = power(T, n - 1);
    return T.m;
}

int main()
{
    fastio;

    long long n;
    cin >> n;
    cout << fib(n) << endl;
}