#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

struct Node{
    int L = -1, R = -1, val = 0;
};

struct PST{

    vector <Node> node;
    int root[MX];

    void init_segtree(int nL, int nR){
        if(nL == nR) return;
        int n = node.size() - 1;
        int mid = nL + nR >> 1;
        node[n].L = node.size();
        node.push_back(Node());
        init_segtree(nL, mid);
        node[n].R = node.size();
        node.push_back(Node());
        init_segtree(mid + 1, nR);
    }

    void add_segtree(int p, int tar, int nL, int nR){
        int n = node.size() - 1;
        if(nL == nR){
            node[n].val = 1;
            return;
        }
        int mid = nL + nR >> 1;
        if(tar <= mid){
            node[n].R = node[p].R;
            node[n].L = node.size();
            node.push_back(Node());
            add_segtree(node[p].L, tar, nL, mid);
        }else{
            node[n].L = node[p].L;
            node[n].R = node.size();
            node.push_back(Node());
            add_segtree(node[p].R, tar, mid + 1, nR);
        }
        node[n].val = node[node[n].L].val + node[node[n].R].val;
    }

    int Query(int n, int L, int R, int nL, int nR){
        if(L == nL && R == nR) return node[n].val;
        int mid = nL + nR >> 1;
        if(R <= mid) return Query(node[n].L, L, R, nL, mid);
        if(L > mid) return Query(node[n].R, L, R, mid + 1, nR);
        return Query(node[n].L, L, mid, nL, mid) + Query(node[n].R, mid + 1, R, mid + 1, nR);
    }

}pst;

int N, M, X, Y, K, h[MX], w[MX], par[MX][20];
bool visit[MX];

int getLCA(int u, int v){
    if(h[u] < h[v]) swap(u, v);
    int gap = h[u] - h[v];
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            gap ^= (1 << i);
            u = par[u][i];
        }
    }
    if(u == v) return u;
    for(int j = 19; j >= 0; j--){
        if(par[u][j] != par[v][j]) u = par[u][j], v = par[v][j];
    }
    return par[u][0];
}

map <int, int> mp, rev;

vector <int> adj[MX];

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) scanf("%d", &w[i]), mp.insert({w[i], 0});
    for(int i = 0; i < N - 1; i++){
        scanf("%d %d", &X, &Y);
        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }
    int cnt = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) it->second = ++cnt, rev.insert({cnt, it->first});
    for(int i = 1; i <= N; i++) w[i] = mp[w[i]];
    pst.node.push_back(Node());
    pst.init_segtree(1, N);
    queue <int> q;
    par[1][0] = 0;
    q.push(1), visit[1] = true;
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        pst.root[pos] = pst.node.size();
        pst.node.push_back(Node());
        pst.add_segtree(pst.root[par[pos][0]], w[pos], 1, N);
        for(int next : adj[pos]){
            if(!visit[next]){
                par[next][0] = pos;
                h[next] = h[pos] + 1;
                q.push(next), visit[next] = true;
            }
        }
    }
    for(int j = 1; j < 20; j++)
    for(int i = 1; i <= N; i++) par[i][j] = par[par[i][j - 1]][j - 1];
    for(int i = 0; i < M; i++){
        scanf("%d %d %d", &X, &Y, &K);
        int lo = 1, hi = N, P = getLCA(X, Y);
        while(lo < hi){
            int mid = lo + hi >> 1;
            cnt = pst.Query(pst.root[X], 1, mid, 1, N) + pst.Query(pst.root[Y], 1, mid, 1, N) - pst.Query(pst.root[P], 1, mid, 1, N) - pst.Query(pst.root[par[P][0]], 1, mid, 1, N);
            if(cnt < K) lo = mid + 1;
            else if(cnt >= K) hi = mid;
        }
        printf("%d\n", rev[lo]);
    }
}
/*
6 100000
1 3 4 2 0 5
1 2
2 3
2 4
4 5
4 6
*/
