#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;

#define rep(i, n) for (int i = 0; i < n; i++)

// Matrix class
struct Matrix{
    vvl m;
    int n;
    Matrix(int n, bool ident = false) : n(n)
    {
        m.assign(n, vector<ll>(n, 0));
        if (ident)
            rep(i, n) m[i][i] = 1;
    }
};

// Multiply two matrices (mod MOD)
Matrix multiply(const Matrix &A, const Matrix &B){
    int n = A.n;
    Matrix C(n);
    rep(i, n) rep(k, n){
        if (A.m[i][k] == 0)
            continue;
        rep(j, n)
            C.m[i][j] = (C.m[i][j] + A.m[i][k] * B.m[k][j]) % MOD;
    }
    return C;
}

// Fast exponentiation of matrix
Matrix power(Matrix A, ll exp){
    int n = A.n;
    Matrix res(n, true); // identity
    while (exp){
        if (exp & 1)
            res = multiply(res, A);
        A = multiply(A, A);
        exp >>= 1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<ll> c(k), a(k);
    rep(i, k) cin >> a[i]; // initial a1..ak
    rep(i, k) cin >> c[i]; // coefficients c1..ck
    ll n;
    cin >> n;

    // If n <= k, directly return a[n-1]
    if (n <= k) {
        cout << a[n - 1] % MOD << "\n";
        return 0;
    }

    // Build transition matrix of size k×k
    Matrix T(k);
    rep(j, k) T.m[0][j] = c[j] % MOD; // first row = coefficients
    for (int i = 1; i < k; i++) T.m[i][i - 1] = 1; // subdiagonal = 1

    // Compute T^(n-k)
    Matrix Tn = power(T, n - k);

    // Compute a_n = first row of T^(n-k) * [a_k, a_{k-1}, ..., a_1]^T
    ll ans = 0;
    rep(j, k) ans = (ans + Tn.m[0][j] * a[k - 1 - j]) % MOD;

    cout << ans << "\n";
    return 0;
}
