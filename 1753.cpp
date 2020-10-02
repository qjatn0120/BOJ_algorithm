#include <bits/stdc++.h>

using namespace std;

const int MX = 2e4 + 5;
const int inf = 987654321;

int V, E, S, u, v, w, dist[MX];
vector <pair<int, int> > adj[MX];

int main(){
    scanf("%d %d%d", &V, &E, &S);
    for(int i = 0; i < E; i++){
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back({v, w});
    }
    fill(dist + 1, dist + V + 1, inf);
    priority_queue <pair<int, int> > pq;//pq => 큰 값을 root
    dist[S] = 0;
    pq.push({0, S});
    while(!pq.empty()){
        pair <int, int> info = pq.top();
        pq.pop();
        int pos = info.second, cost = -info.first;
        for(auto i : adj[pos]){
            int next = i.first, nextCost = cost + i.second;
            if(nextCost < dist[next]){
                dist[next] = nextCost;
                pq.push({-nextCost, next});
            }
        }
    }
    for(int i = 1; i <= V; i++){
        if(dist[i] == inf) printf("INF\n");
        else printf("%d\n", dist[i]);
    }
}
