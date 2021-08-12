#include <bits/stdc++.h>

using namespace std;

const int MAX_NODE = 30005;
int V;

struct SegmentTree{

    int tree[MAX_NODE * 4];

    void Update(int n, int tar, int nL, int nR, int c){
        if(nL == nR){
            tree[n] = c;
            return;
        }

        int mid = (nL + nR) >> 1;
        if(tar <= mid) Update(n * 2, tar, nL, mid, c);
        else Update(n * 2 + 1, tar, mid + 1, nR, c);
        tree[n] = tree[n * 2] + tree[n * 2 + 1];
    }

    int Query(int n, int l, int r, int nL, int nR){
        if(l > nR || r < nL) return 0;
        if(l <= nL && nR <= r) return tree[n];

        int mid = (nL + nR) >> 1;
        return Query(n * 2, l, r, nL, mid) + Query(n * 2 + 1, l, r, mid + 1, nR);
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
        idx = 0;
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

    void Update(int n, int c){
        seg.Update(1, in[n], 1, V, c);
    }

    int Query(int u, int v){
        int ret = 0;
        while(top[u] ^ top[v]){
            if(dep[top[u]] < dep[top[v]]) swap(u, v);
            int st = top[u];
            ret += seg.Query(1, in[st], in[u], 1, V);
            u = par[st];
        }

        if(dep[u] > dep[v]) swap(u, v);
        ret += seg.Query(1, in[u], in[v], 1, V);
        return ret;
    }

}hld;

struct Query{
    int type, a, b;
    Query(string s, int a, int b) : a(a), b(b){
        if(s == "bridge") type = 0;
        else if(s == "penguins") type = 1;
        else type = 2;
    }
};

struct UnionFind{

    int par[MAX_NODE];

    void Clear(int sz){
        iota(par + 1, par + sz + 1, 1);
    }

    int Find(int u){
        if(par[u] == u) return u;
        return par[u] = Find(par[u]);
    }

    bool Union(int u, int v){
        u = Find(u), v = Find(v);
        if(u == v) return false;
        par[u] = v;
        return true;
    }

}uf;

vector <Query> query;
string str;
int N, Q, a, b, num[MAX_NODE];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    V = N;
    for(int i = 1; i <= N; i++) cin >> num[i];
    cin >> Q;

    for(int i = 0; i < Q; i++){
        cin >> str >> a >> b;
        query.emplace_back(str, a, b);
    }

    uf.Clear(N);
    for(auto &q : query){
        if(q.type == 0){
            if(uf.Union(q.a, q.b)) hld.addEdge(q.a, q.b);
        }
    }

    hld.init();
    for(int i = 1; i <= N; i++) hld.Update(i, num[i]);

    uf.Clear(N);
    for(auto &q : query){
        if(q.type == 0){
            if(uf.Union(q.a, q.b)) cout << "yes\n";
            else cout << "no\n";
        }else if(q.type == 1){
            hld.Update(q.a, q.b);
        }else{
            if(uf.Find(q.a) != uf.Find(q.b)) cout << "impossible\n";
            else cout << hld.Query(q.a, q.b) << "\n";
        }
    }
}
