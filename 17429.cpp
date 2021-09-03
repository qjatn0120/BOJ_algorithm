#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAX_NODE = 5e5 + 5;
const ull MOD = (1LL << 32);

int V;

struct SegmentTree {
    ull tree[MAX_NODE * 4], lazy1[MAX_NODE * 4], lazy2[MAX_NODE * 4];

    void Clear(){
        for(int i = 1; i <= V * 4; i++) lazy2[i] = 1;
    }

    void prop1(int n, int nL, int nR){
        tree[n] = (tree[n] + lazy1[n] * (nR - nL + 1)) % MOD;
        if(nL != nR){
            lazy1[n * 2] = (lazy1[n] + lazy1[n * 2]) % MOD;
            lazy1[n * 2 + 1] = (lazy1[n] + lazy1[n * 2 + 1]) % MOD;
        }
        lazy1[n] = 0;
    }

    void prop2(int n, int nL, int nR){
        tree[n] = (tree[n] * lazy2[n]) % MOD;
        if(nL != nR){
            lazy1[n * 2] = (lazy2[n] * lazy1[n * 2]) % MOD;
            lazy2[n * 2] = (lazy2[n] * lazy2[n * 2]) % MOD;
            lazy1[n * 2 + 1] = (lazy2[n] * lazy1[n * 2 + 1]) % MOD;
            lazy2[n * 2 + 1] = (lazy2[n] * lazy2[n * 2 + 1]) % MOD;
        }
        lazy2[n] = 1;
    }

    void Update(int n, int l, int r, int nL, int nR, int c, bool type){
        if(lazy2[n] != 1) prop2(n, nL, nR);
        if(lazy1[n]) prop1(n, nL, nR);
        if(r < nL || l > nR) return;
        if(l <= nL && nR <= r){
            if(!type){
                lazy1[n] = (lazy1[n] + c) % MOD;
                prop1(n, nL, nR);
            }else{
                lazy2[n] = (lazy2[n] * c) % MOD;
                prop2(n, nL, nR);
            }
            return;
        }

        int mid = (nL + nR) >> 1;
        Update(n * 2, l, r, nL, mid, c, type);
        Update(n * 2 + 1, l, r, mid + 1, nR, c, type);
        tree[n] = (tree[n * 2] + tree[n * 2 + 1]) % MOD;
    }

    ull Query(int n, int l, int r, int nL, int nR){
        if(lazy2[n] != 1) prop2(n, nL, nR);
        if(lazy1[n]) prop1(n, nL, nR);
        if(r < nL || l > nR) return 0LL;
        if(l <= nL && nR <= r) return tree[n];
        int mid = (nL + nR) >> 1;
        return (Query(n * 2, l, r, nL, mid) + Query(n * 2 + 1, l, r, mid + 1, nR)) % MOD;
    }
};

struct HeavyLightDecomposition{

    vector <int> adj[MAX_NODE];
    vector <int> child[MAX_NODE];
    int sz[MAX_NODE], dep[MAX_NODE], par[MAX_NODE], top[MAX_NODE], in[MAX_NODE], out[MAX_NODE];
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
        out[pos] = idx;
    }

    void Clear(){
        for(int i = 1; i <= V; i++) adj[i].clear(), child[i].clear();
        for(int i = 1; i <= V; i++) sz[i] = dep[i] = top[i] = 0;
        idx = 0;
        seg.Clear();
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init(){
        for(int i = 1; i <= V; i++){
            if(top[i] == 0){
                dfs1(i);
                top[i] = i;
                dfs2(i);
            }
        }
    }

    void Update1(int u, int c, bool type){
        seg.Update(1, in[u], out[u], 1, V, c, type);
    }

    void Update2(int u, int v, int c, bool type){
        while(top[u] ^ top[v]){
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            int st = top[u];
            seg.Update(1, in[st], in[u], 1, V, c, type);
            u = par[st];
        }

        if(dep[u] > dep[v]) swap(u, v);
        seg.Update(1, in[u], in[v], 1, V, c, type);
    }

    ull Query1(int u){
        return seg.Query(1, in[u], out[u], 1, V);
    }

    ull Query2(int u, int v){
        ull ret = 0;
        while(top[u] ^ top[v]){
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            int st = top[u];
            ret = (ret + seg.Query(1, in[st], in[u], 1, V)) % MOD;
            u = par[st];
        }

        if(dep[u] > dep[v]) swap(u, v);
        ret = (ret + seg.Query(1, in[u], in[v], 1, V)) % MOD;
        return ret;
    }

}hld;

int N, Q, s, e, a, b, c, d;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> Q;
    V = N;
    hld.Clear();
    for(int i = 1; i < N; i++){
        cin >> s >> e;
        hld.addEdge(s, e);
    }
    hld.init();

    while(Q--){
        cin >> a;
        if(a == 1 || a == 3){
            cin >> b >> c;
            hld.Update1(b, c, a == 3);
        }else if(a == 2 || a == 4){
            cin >> b >> c >> d;
            hld.Update2(b, c, d, a == 4);
        }else if(a == 5){
            cin >> b;
            cout << hld.Query1(b) << "\n";
        }else{
            cin >> b >> c;
            cout << hld.Query2(b, c) << "\n";
        }
    }
}
