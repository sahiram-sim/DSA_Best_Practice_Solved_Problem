#include <bits/stdc++.h>
using namespace std;

// | Situation                 | Method                           | Complexity        | Notes               |
// | ------------------------- | -------------------------------- | ----------------- | ------------------- |
// | n, r ≤ 10⁶                | Precompute factorials            | O(1)/query        | Simple              |
// | n large, p small prime    | Lucas Theorem                    | O(logₚ n)         | Perfect for large n |
// | p composite               | Lucas + CRT                      | O(logₚ n + CRT)   | Advanced math       |
// | n large, multiple queries | Precompute factorials mod p once | O(logₚ n / query) | Efficient           |

const int MAXP = 100000; // should be >= p
long long fact[MAXP];
long long MOD; // the prime

long long modpow(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

long long modInverse(long long a, long long p) {
    return modpow(a, p - 2, p); // Fermat (p is prime)
}

void initFactorials(long long p) {
    MOD = p;
    fact[0] = 1;
    for (int i = 1; i < p; i++)
        fact[i] = (fact[i - 1] * i) % p;
}


long long nCr_mod_p_small(long long n, long long r, long long p) {
    if (r > n) return 0;
    return fact[n] * modInverse(fact[r], p) % p * modInverse(fact[n - r], p) % p;
}

long long nCr_Lucas(long long n, long long r, long long p) {
    if (r == 0) return 1;
    long long ni = n % p;
    long long ri = r % p;
    return nCr_Lucas(n / p, r / p, p) * nCr_mod_p_small(ni, ri, p) % p;
}

int main() {
    long long n = 1000000000000LL; // 1e12
    long long r = 12345;
    long long p = 13; // small prime

    initFactorials(p);
    cout << nCr_Lucas(n, r, p) << "\n";
}
