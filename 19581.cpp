#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

vector <pair<int, int> > adj[MX];

int N, A, B, C;
long long int dist[MX];

int maxDist(int p){
    queue <int> q;
    q.push(p);
    fill(dist, dist + MX, LONG_LONG_MAX / 10);
    dist[p] = 0;
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(auto i : adj[pos]){
            int next = i.first, cost = i.second;
            if(dist[next] == LONG_LONG_MAX / 10){
                dist[next] = dist[pos] + cost;
                q.push(next);
            }
        }
    }
    return max_element(dist + 1, dist + N + 1) - dist;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i < N; i++){
        cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    int L = maxDist(1);
    int R = maxDist(L);
    dist[R] = 0;
    long long int ans = *max_element(dist + 1, dist + N + 1);
    maxDist(R), dist[L] = 0;
    ans = max(ans, *max_element(dist + 1, dist + N + 1));
    cout << ans;
}
