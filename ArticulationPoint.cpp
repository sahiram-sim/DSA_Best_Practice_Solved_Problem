#include <bits/stdc++.h>
using namespace std;

// Aliases for convenience
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

// Loop macros
#define fr(i, l, r) for (int i = (l); i < (r); i++)
#define all(x) (x).begin(), (x).end()

vector<vector<int>> adj;
vector<int> low, disc, parent;
vector<bool> vis;
int n, m;
vector<bool> ap;
vector<pair<int, int>> bridges;

class Graph
{
private:
    int n;                // Number of nodes
    vvi adj;              // Adjacency list
    vi disc, low, parent; // Discovery & Low values, parent tracking
    vector<bool> vis, ap; // Visited & articulation points
    vector<pii> bridges;  // List of bridges
    int timer;            // Global DFS timer
};

void DFS(int u, int &timer)
{
    disc[u] = low[u] = ++timer;
    vis[u] = true;
    int children = 0;

    for (auto v : adj[u])
    {
        if (!vis[v])
        {
            parent[v] = u; // Set parent of v
            DFS(v, timer);
            children++;

            low[u] = min(low[u], low[v]);

            // (1) u is root and has more than one child
            if (parent[u] == -1 && children > 1)
            {
                ap[u] = true;
            }

            // (2) u is not root and low[v] >= disc[u]
            if (parent[u] != -1 && low[v] >= disc[u])
            {
                ap[u] = true;
            }

            // (3) Bridge condition
            if (low[v] > disc[u])
            {
                bridges.push_back({u, v});
            }
        }
        else if (v != parent[u]) // Check for back edge
        {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main()
{
    n = 8, m = 7;
    adj.resize(n);
    disc.resize(n, -1);
    low.resize(n, -1);
    parent.resize(n, -1);
    vis.resize(n, false);
    ap.resize(n, false);

    // Defining edges
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(3);
    adj[3].push_back(2);

    adj[3].push_back(4);
    adj[4].push_back(3);

    adj[4].push_back(5);
    adj[5].push_back(4);

    adj[5].push_back(6);
    adj[6].push_back(5);

    adj[5].push_back(7);
    adj[7].push_back(5);

    int timer = 0;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            DFS(i, timer);
    }

    // Print articulation points
    cout << "Here are the articulation points: " << endl;
    for (int i = 0; i < n; i++)
    {
        if (ap[i])
            cout << i << " " << endl;
    }

    // Print bridges
    cout << "Here are the Bridges nodes: " << endl;
    for (auto b : bridges)
    {
        cout << b.first << " " << b.second << endl;
    }

    return 0;
}
