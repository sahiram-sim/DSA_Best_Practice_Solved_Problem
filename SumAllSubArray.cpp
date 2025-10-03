#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int64> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    // Prefix sums
    vector<int64> P0(N + 1), P1(N + 1), P2(N + 1);
    for (int i = 1; i <= N; i++) {
        P0[i] = P0[i - 1] + A[i];            // sum A[k]
        P1[i] = P1[i - 1] + i * A[i];        // sum k*A[k]
        P2[i] = P2[i - 1] + 1LL * i * i * A[i]; // sum k^2*A[k]
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;

        int64 S0 = P0[R] - P0[L - 1]; // sum A[k]
        int64 S1 = P1[R] - P1[L - 1]; // sum k*A[k]
        int64 S2 = P2[R] - P2[L - 1]; // sum k^2*A[k]

        // Formula derived: 
        // Answer = (R+1)*(S1 - (L-1)*S0) - (S2 - (L-1)*S1)
        int64 ans = (R + 1) * (S1 - (int64)(L - 1) * S0) 
                  - (S2 - (int64)(L - 1) * S1);

        cout << ans << "\n";
    }

    return 0;
}
