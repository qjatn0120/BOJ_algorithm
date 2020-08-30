#include <bits/stdc++.h>

using namespace std;

const int MX = 205;
const int inf = 987654321;

struct MCMF{
    int c[MX][MX];
    int d[MX][MX];
    vector <int> adj[MX];

    void Clear(){
        for(int i = 0; i < MX * MX; i++){
            c[i / MX][i % MX] = 0;
            d[i / MX][i % MX] = inf;
        }
    }

    void AddEdge(int u, int v, int f, int cost){
        c[u][v] = f;
        d[u][v] = cost;
        d[v][u] = -cost;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    pair <int, int> getMCMF(int S, int E){
        pair <int, int> ret;
        while(1){
            int dist[MX], prev[MX];
            bool inQ[MX] = {};
            fill(dist, dist + MX, inf);
            memset(prev, -1, sizeof(prev));
            queue <int> q;
            q.push(S);
            dist[S] = 0;
            while(!q.empty()){
                int pos = q.front();
                q.pop();
                inQ[pos] = false;
                for(auto next : adj[pos]){
                    if(c[pos][next] && dist[next] > dist[pos] + d[pos][next]){
                        dist[next] = dist[pos] + d[pos][next];
                        prev[next] = pos;
                        if(!inQ[next]) q.push(next), inQ[next] = true;
                    }
                }
            }
            if(prev[E] == -1) break;

            int flow = inf, cost = 0;
            for(int pos = E; pos != S; pos = prev[pos]){
                flow = min(c[prev[pos]][pos], flow);
                cost += d[prev[pos]][pos];
            }
            for(int pos = E; pos != S; pos = prev[pos]){
                c[prev[pos]][pos] -= flow;
                c[pos][prev[pos]] += flow;
            }
            ret.first += flow, ret.second += flow * cost;
        }
        return ret;
    }
}mcmf;

int N, M, a, C[MX][MX], D[MX][MX];

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++){
        scanf("%d", &a);
        mcmf.AddEdge(i + 100, 201, a, 0);
    }
    for(int i = 1; i <= M; i++){
        scanf("%d", &a);
        mcmf.AddEdge(0, i, a, 0);
    }
    for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N; j++) scanf("%d", &C[i][j]);
    for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N; j++) scanf("%d", &D[i][j]);
    for(int i = 1; i <= M; i++)
    for(int j = 1; j <= N; j++) mcmf.AddEdge(i, 100 + j, C[i][j], D[i][j]);
    auto ans = mcmf.getMCMF(0, 201);
    printf("%d\n%d", ans.first, ans.second);
}
