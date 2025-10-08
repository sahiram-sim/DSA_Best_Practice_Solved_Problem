#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 3x3 Matrix type
struct Matrix {
    ll m[3][3];
};

// Matrix multiplication (3x3)
Matrix multiply(Matrix a, Matrix b, ll mod = LLONG_MAX) {
    Matrix c = {0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                c.m[i][j] = (c.m[i][j] + a.m[i][k] * b.m[k][j]) % mod;
    return c;
}

// Fast matrix exponentiation
Matrix power(Matrix base, long long exp, ll mod = LLONG_MAX) {
    Matrix result = {{{1,0,0},{0,1,0},{0,0,1}}}; // Identity matrix
    while (exp > 0) {
        if (exp & 1)
            result = multiply(result, base, mod);
        base = multiply(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Tribonacci function
long long tribonacci(long long n, ll mod = LLONG_MAX) {
    if (n == 0) return 0;
    if (n == 1) return 0;
    if (n == 2) return 1;

    Matrix A = {{{1,1,1},{1,0,0},{0,1,0}}};
    Matrix An = power(A, n - 2, mod);

    // T_n = [1 0 0] * A^(n-2) * [1,0,0]^T
    ll Tn = (An.m[0][0] * 1 + An.m[0][1] * 0 + An.m[0][2] * 0) % mod;
    return Tn;
}

int main() {
    long long n;
    cout << "Enter n: ";
    cin >> n;

    cout << "T(" << n << ") = " << tribonacci(n) << "\n";

    // Example: if n=5, output should be 4
    return 0;
}
