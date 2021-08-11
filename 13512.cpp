#include <bits/stdc++.h>

using namespace std;

const int MAX_NODE = 1e5 + 5;
int N, M, u, v;

struct SegmentTree{

    int tree[MAX_NODE * 4];

    void Update(int n, int tar, int nL, int nR, int c){
        if(nL == nR){
            tree[n] ^= c;
            return;
        }

        int mid = (nL + nR) >> 1;
        if(tar <= mid) Update(n * 2, tar, nL, mid, c);
        else Update(n * 2 + 1, tar, mid + 1, nR, c);

        tree[n] = tree[n * 2] ? tree[n * 2] : tree[n * 2 + 1];
    }

    int Query(int n, int l, int r, int nL, int nR){
        if(l > nR || r < nL) return 0;
        if(l <= nL && nR <= r) return tree[n];

        int mid = (nL + nR) >> 1;
        int x1 = Query(n * 2, l, r, nL, mid), x2 = Query(n * 2 + 1, l, r, mid + 1, nR);
        return x1 ? x1 : x2;
    }

};

struct HeavyLightDecomposition{

    vector <int> adj[MAX_NODE];
    vector <int> child[MAX_NODE];
    int sz[MAX_NODE], dep[MAX_NODE], par[MAX_NODE], top[MAX_NODE], in[MAX_NODE];
    int idx;

    SegmentTree seg;

    void dfs1(int pos){
        sz[pos] = 1;
        for(int next : adj[pos]){
            if(sz[next]) continue;
            par[next] = pos;
            dep[next] = dep[pos] + 1;
            dfs1(next);
            sz[pos] += sz[next];
            child[pos].push_back(next);
            if(sz[next] > sz[child[pos][0]]) swap(child[pos][0], child[pos].back());
        }
    }

    void dfs2(int pos){
        in[pos] = ++idx;
        for(int next : child[pos]){
            if(next == child[pos][0]) top[next] = top[pos];
            else top[next] = next;
            dfs2(next);
        }
    }

    void Clear(int n){
        for(int i = 1; i <= n; i++) adj[i].clear(), child[i].clear();
        for(int i = 1; i <= n; i++) sz[i] = dep[i] = 0;
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(){
        dfs1(1);
        top[1] = 1;
        dfs2(1);
    }

    void Update(int n){
        seg.Update(1, in[n], 1, N, n);
    }

    int Query(int u){
        int ret = -1;
        while(top[u] ^ top[1]){
            int st = top[u];
            int res = seg.Query(1, in[st], in[u], 1, N);
            if(res) ret = res;
            u = par[st];
        }

        int res = seg.Query(1, 1, in[u], 1, N);
        if(res) ret = res;

        return ret;
    }

}hld;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i < N; i++){
        cin >> u >> v;
        hld.addEdge(u, v);
    }
    hld.init();

    cin >> M;
    while(M--){
        cin >> u >> v;
        if(u == 1) hld.Update(v);
        else cout << hld.Query(v) << "\n";
    }
}
