#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

/*
10 200
1 2 1
1 3 6
2 4 3
2 5 4
3 6 5
3 7 4
3 8 3
6 9 1
7 10 2
*/

vector <pair<int, int> > adj[MX];
int N, Q, A, B, C, S, E, h[MX], par[MX][20], dist[MX][20], node[MX * 4], arr[MX];

int getLCA(int p, int q){
    if(h[p] < h[q]) swap(p, q);
    int gap = h[p] - h[q];
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            gap ^= (1 << i);
            p = par[p][i];
        }
    }
    if(p == q) return p;
    for(int i = 19; i >= 0; i--){
        if(par[p][i] != par[q][i]) p = par[p][i], q = par[q][i];
    }
    return par[p][0];
}

int getDist(int p, int c){//parent and child
    int gap = h[c] - h[p], ret = 0;
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            ret = max(ret, dist[c][i]);
            c = par[c][i];
            gap ^= (1 << i);
        }
    }
    return ret;
}

void makeTree(int n, int nL, int nR){
    if(nL == nR){
        node[n] = arr[nL];
        return;
    }
    int mid = nL + nR >> 1;
    makeTree(n * 2, nL, mid);
    makeTree(n * 2 + 1, mid + 1, nR);
    node[n] = max(node[n * 2], node[n * 2 + 1]);
}

int Query(int n, int L, int R, int nL, int nR){
    if(nL == L && nR == R) return node[n];
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(n * 2, L, R, nL, mid);
    if(L > mid) return Query(n * 2 + 1, L, R, mid + 1, nR);
    return max(Query(n * 2, L, mid, nL, mid), Query(n * 2 + 1, mid + 1, R, mid + 1, nR));
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 0; i < N - 1; i++){
        scanf("%d %d %d", &A, &B, &C);
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    bool visited[MX] = {};
    queue <int> q;
    q.push(1);
    visited[1] = true;
    par[1][0] = 1;
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(auto i : adj[pos]){
            int next = i.first, cost = i.second;
            if(!visited[next]){
                par[next][0] = pos;
                dist[next][0] = cost;
                h[next] = h[pos] + 1;
                visited[next] = true;
                q.push(next);
            }
        }
    }
    for(int j = 1; j < 20; j++)
    for(int i = 1; i <= N; i++){
        par[i][j] = par[par[i][j - 1]][j - 1];
        dist[i][j] = max(dist[i][j - 1], dist[par[i][j - 1]][j - 1]);
    }
    for(int i = 1; i < N; i++){
        int p = getLCA(i, i + 1);
        arr[i] = max(getDist(p, i), getDist(p, i + 1));
    }
    if(N > 1) makeTree(1, 1, N - 1);
    while(Q--){
        scanf("%d %d", &S, &E);
        printf("%d\n", S == E ? 0 : Query(1, S, E - 1, 1, N - 1));
    }
}
