#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;

int N, M, A, B, C;
vector <pair<int, int> > adj[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < N - 1; i++){
        cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    for(int i = 0; i < M; i++){
        cin >> A >> B;
        int dist[MX];
        memset(dist, -1, sizeof(dist));
        queue <int> q;
        dist[A] = 0;
        q.push(A);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            for(auto i : adj[pos]){
                int next = i.first, cost = i.second;
                if(dist[next] != -1) continue;
                dist[next] = dist[pos] + cost;
                q.push(next);
            }
        }
        cout << dist[B] << "\n";
    }

}
