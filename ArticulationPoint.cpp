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

    void dfs(int u)
    {
        disc[u] = low[u] = ++timer;
        vis[u] = true;
        int children = 0;

        for (int v : adj[u])
        {
            if (!vis[v])
            {
                parent[v] = u;
                dfs(v);
                children++;

                low[u] = min(low[u], low[v]);

                // Root with 2+ children
                if (parent[u] == -1 && children > 1)
                    ap[u] = true;

                // Non-root with back edge condition
                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;

                // Bridge condition
                if (low[v] > disc[u])
                    bridges.push_back({u, v});
            }
            else if (v != parent[u])
            {
                // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int nodes) : n(nodes), adj(nodes), disc(nodes, -1),
                       low(nodes, -1), parent(nodes, -1), vis(nodes, false),
                       ap(nodes, false), timer(0) {}

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void findArticulationPointsAndBridges()
    {
        fr(i, 0, n)
        {
            if (!vis[i])
                dfs(i);
        }
    }

    void printResults()
    {
        cout << "Articulation Points:\n";
        fr(i, 0, n)
        {
            if (ap[i])
                cout << i << "\n";
        }

        cout << "\nBridges:\n";
        for (auto [u, v] : bridges)
        {
            cout << u << " " << v << "\n";
        }
    }
};
// ----------------------------
// Driver Code
// ----------------------------
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 8, m = 7;
    Graph g(n);

    // Define edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(5, 7);

    g.findArticulationPointsAndBridges();
    g.printResults();

    return 0;
}