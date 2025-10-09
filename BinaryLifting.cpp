#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
int up[100001][21];
const int LOG = 19;

vi depth;
vvi adj;
int n;

void dfs(int node, int p){
    up[node][0] = p;
    for(int i=0;i<LOG; i++){
        if(up[node][i-1] !=-1) up[node][i] = up[up[u][i-1]][i-1];
        else up[node][i] = -1;
    }
    for(auto v : adj[node]){
        if(v!=p){
            depth[v] = 1 + depth[node];
            dfs(v, node);
        }
    }
}

int lift(int u, int k){
    for(int i = 0; i < LOG; i++){
        if(k & (1<<i)) u = up[u][i];
    }
    return 
}

int LCA(int u, int v){
    if(depth[u] < depth[v]) swap(u, v);
    u = lift(u, depth[u] - depth[v]);
    
    for(int i = LOG; i >= 0; i--){
        if(up[u][i] != up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

void BinaryLifting(){
    cin>>n;
    depth.assign(n+1, 0);
    depth[0] = 0;
    adj.resize(n+1);
    memset(up, -1, sizeof(up));
    adj[1].push_back({2, 3});
    adj[2].push_back({4, 5});
    adj[3].push_back({6});
    adj[5].push_back({7, 8});
    adj[8].push_back({9});
    
    dfs(1, -1);
    
    cout<<LCA(2,3)<<endl;
}

int main()
{
    BinaryLifting();

    return 0;
}