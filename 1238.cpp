#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;
const int inf = 987654321;

int N, M, A, B, T, X;

struct dijkstra{

    vector <pair<int, int> > adj[MX];
    int dist[MX];

    void AddEdge(int u, int v, int w){
        adj[u].push_back({v, w});
    }

    void getDist(int S){
        fill(dist + 1, dist + N + 1, inf);
        priority_queue <pair<int, int> > pq;
        dist[S] = 0;
        pq.push({0, S});
        while(!pq.empty()){
            auto tmp = pq.top();
            pq.pop();
            int pos = tmp.second, cost = -tmp.first;
            for(auto i : adj[pos]){
                int next = i.first, nextCost = cost + i.second;
                if(dist[next] > nextCost){
                    dist[next] = nextCost;
                    pq.push({-nextCost, next});
                }
            }
        }
    }
}g1, g2;

int main(){
    scanf("%d %d %d", &N, &M, &X);
    for(int i = 0; i < M; i++){
        scanf("%d %d %d", &A, &B, &T);
        g1.AddEdge(A, B, T);
        g2.AddEdge(B, A, T);
    }
    g1.getDist(X);
    g2.getDist(X);
    int ans = 0;
    for(int i = 1; i <= N; i++) ans = max(ans, g1.dist[i] + g2.dist[i]);
    printf("%d", ans);
}
