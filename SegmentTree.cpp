#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> t;

    SegmentTree() : n(0) {}
    SegmentTree(const vector<long long>& a) { build(a); }

    void build(const vector<long long>& a) {
        n = (int)a.size();
        t.assign(4*n, 0);
        build(1, 0, n-1, a);
    }

    void build(int v, int tl, int tr, const vector<long long>& a) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm, a);
            build(v*2+1, tm+1, tr, a);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    // point assign: a[pos] = val
    void update(int pos, long long val) { update(1, 0, n-1, pos, val); }
    void update(int v, int tl, int tr, int pos, long long val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v*2, tl, tm, pos, val);
            else update(v*2+1, tm+1, tr, pos, val);
            t[v] = t[v*2] + t[v*2+1];
        }
    }

    // range sum on [l, r]
    long long query(int l, int r) const { 
        if (l > r) return 0;
        return query(1, 0, n-1, l, r); 
    }
    long long query(int v, int tl, int tr, int l, int r) const {
        if (l > r) return 0;
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) / 2;
        return query(v*2, tl, tm, l, min(r, tm))
             + query(v*2+1, tm+1, tr, max(l, tm+1), r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Open files
    ifstream in("segInput.txt");
    ofstream out("segOutput.txt");
    if (!in.is_open()) {
        cerr << "Error: could not open segInput.txt\n";
        return 1;
    }
    if (!out.is_open()) {
        cerr << "Error: could not create segOutput.txt\n";
        return 1;
    }

    // Format for each test:
    // n q
    // a1 a2 ... an
    // then q lines of queries:
    //   type l r         (for type==1 range sum)
    //   type idx val     (for type==2 point assign)
    //
    // You can append multiple tests one after another in the same file.
    while (true) {
        int n, q;
        if (!(in >> n >> q)) break;  // end-of-file cleanly

        vector<long long> arr(n);
        for (int i = 0; i < n; ++i) in >> arr[i];

        SegmentTree sg(arr);

        for (int i = 0; i < q; ++i) {
            int type; 
            in >> type;
            switch (type) {
                case 1: { // sum on [l, r] (1-based in input)
                    int l, r;
                    in >> l >> r;
                    --l; --r;                      // to 0-based
                    if (l > r) swap(l, r);         // be forgiving
                    long long ans = sg.query(l, r);
                    out << ans << "\n";            // one line per query
                    break;
                }
                case 2: { // point update: arr[idx] = val (1-based idx)
                    int idx; long long val;
                    in >> idx >> val;
                    --idx;                         // to 0-based
                    if (0 <= idx && idx < n) sg.update(idx, val);
                    break;
                }
                default: {
                    // Unknown query type: consume the rest of line safely
                    // (optional) you could log or ignore
                    break;
                }
            }
        }
        // no extra separators; outputs are just the answers of type-1 queries
    }

    return 0;
}
