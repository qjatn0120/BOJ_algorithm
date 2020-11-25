#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;
const int inf = 987654321;
int N, M, s, e, d;

vector <pair<int, int> > adj[MX];

int SPFA(int S){
    bool inQ[MX];
    int dist[MX];
    pair <int, int> bef[MX];
    memset(inQ, 0, sizeof(inQ));
    fill(dist + 1, dist + N + 1, inf);
    queue <int> q;
    q.push(S);
    dist[S] = 0;
    while(!q.empty()){
        int pos = q.front(), i = 0;
        q.pop();
        for(auto tmp : adj[pos]){
            int next = tmp.first, cost = tmp.second + dist[pos];
            if(cost < dist[next]){
                dist[next] = cost;
                bef[next] = {pos, i};
                if(!inQ[next]) q.push(next);
            }
            i++;
        }
    }
    int pos = 2;
    while(pos != S){
        int prev = bef[pos].first, idx = bef[pos].second, cost = adj[prev][idx].second;
        adj[prev].erase(adj[prev].begin() + idx);
        adj[pos].push_back({prev, -cost});
        pos = prev;
    }
    return dist[2];
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        cin >> s >> e >> d;
        adj[s].push_back({e, d});
        adj[e].push_back({s, d});
    }
    cout << SPFA(1) + SPFA(N);
}
