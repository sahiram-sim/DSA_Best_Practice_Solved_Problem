#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int MAXLOG = 20;

int up[MAXN + 1][MAXLOG];
vector<int> depth;
vector<vector<int>> adj;
int n;

void dfs(int u, int p) {
    up[u][0] = p;
    for (int i = 1; i < MAXLOG; i++) {
        if (up[u][i - 1] == -1)
            up[u][i] = -1;
        else
            up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v == p)
            continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int lift(int u, int k) {
    for (int i = 0; i < MAXLOG && u != -1; i++) {
        if (k & (1 << i))
            u = up[u][i];
    }
    return u;
}

int LCA(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    u = lift(u, depth[u] - depth[v]);
    if (u == v)
        return u;

    for (int i = MAXLOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void BinaryLifting() {
    n = 9;
    adj.assign(n + 1, {});
    depth.assign(n + 1, 0);
    memset(up, -1, sizeof(up));

    auto add = [&](int a, int b) { 
        adj[a].push_back(b); adj[b].push_back(a); 
    };

    add(1, 2);
    add(1, 3);
    add(2, 4);
    add(2, 5);
    add(3, 6);
    add(5, 7);
    add(5, 8);
    add(8, 9);

    depth[1] = 0;
    dfs(1, -1);

    cout << LCA(2, 3) << "\n";
}

int main() {
    BinaryLifting();
    return 0;
}
