#include <bits/stdc++.h>

using namespace std;

const int MX = 405;
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

    pair <int, int> maxFlow(int S, int E){
        pair <int, int> ret = {0, 0};
        while(1){
            int prev[MX], dist[MX];
            bool inQ[MX] = {};
            memset(prev, -1, sizeof(prev));
            fill(dist, dist + MX, inf);
            queue <int> q;
            dist[S] = 0;
            q.push(S);
            while(!q.empty()){
                int pos = q.front();
                q.pop();
                inQ[pos] = false;
                for(int next : adj[pos]){
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
                flow = min(flow, c[prev[pos]][pos]);
                cost += d[prev[pos]][pos];
            }

            for(int pos = E; pos != S; pos = prev[pos]){
                c[prev[pos]][pos] -= flow;
                c[pos][prev[pos]] += flow;
            }
            ret.first += flow, ret.second += cost * flow;
        }
        return ret;
    }

}mcmf;

int N, c;

int main(){
    mcmf.Clear();
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++){
        scanf("%d", &c);
        mcmf.AddEdge(i, j + 200, 1, c);
    }
    for(int i = 1; i <= N; i++) mcmf.AddEdge(0, i, 1, 0);
    for(int i = 1; i <= N; i++) mcmf.AddEdge(i + 200, 401, 1, 0);
    printf("%d", mcmf.maxFlow(0, 401).second);
}
