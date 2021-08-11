#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

vector <pair<int, int> > adj[MX];
int par[MX][20], dep[MX], N, M, w, u, v, k;
long long int dist[MX];

void dfs(int pos){
    for(auto edge : adj[pos]){
        int next = edge.first, cost = edge.second;
        if(dist[next] != -1) continue;
        dist[next] = dist[pos] + cost;
        dep[next] = dep[pos] + 1;
        par[next][0] = pos;
        dfs(next);
    }
}

int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    int gap = dep[u] - dep[v];
    for(int j = 0; gap; j++){
        if(gap & 1) u = par[u][j];
        gap >>= 1;
    }

    if(u == v) return u;

    for(int j = 19; j >= 0; j--){
        if(par[u][j] != par[v][j]) u = par[u][j], v = par[v][j];
    }

    return par[u][0];
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i < N; i++){
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    memset(dist, -1, sizeof(dist));
    dist[1] = 0;
    dfs(1);

    for(int j = 1; j < 20; j++)
    for(int i = 1; i <= N; i++) par[i][j] = par[par[i][j - 1]][j - 1];

    cin >> M;
    while(M--){
        cin >> w;
        if(w == 1){
            cin >> u >> v;
            int p = lca(u, v);
            cout << (dist[u] + dist[v] - dist[p] * 2) << "\n";
        }else{
            cin >> u >> v >> k;
            int p = lca(u, v);
            if(dep[u] - dep[p] + 1 < k) swap(u, v), k = dep[u] + dep[v] - dep[p] * 2 + 2 - k;
            k--;
            for(int j = 0; k; j++){
                if(k & 1) u = par[u][j];
                k >>= 1;
            }
            cout << u << "\n";
        }
    }
}
