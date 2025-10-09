#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, sz;
    int comps;

    DSU(int n) {
        par.resize(n+1);
        sz.assign(n+1, 1);
        comps = n;
        iota(par.begin(), par.end(), 0);
    }

    int find(int x) {
        return (par[x] == x) ? x : par[x] = find(par[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        comps--;
        return true;
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }
};

int main() {
    int n = 5;
    DSU dsu(n);

    dsu.unite(1, 2);
    dsu.unite(2, 3);

    cout << dsu.same(1, 3) << "\n"; // 1 (true)
    cout << dsu.same(1, 4) << "\n"; // 0 (false)

    dsu.unite(4, 5);
    cout << "Components = " << dsu.comps << "\n"; // 2
}
