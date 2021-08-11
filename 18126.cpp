#include <bits/stdc++.h>

using namespace std;

const int MX = 5005;

int a, b, c, N;
long long int dist[MX];

vector <pair<int, int> > adj[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i < N; i++){
        cin >> a >> b >> c;
        adj[a].push_back(make_pair(b, c));
        adj[b].push_back(make_pair(a, c));
    }

    queue <int> q;
    memset(dist, -1, sizeof(dist));
    q.push(1);
    dist[1] = 0;
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(auto p : adj[pos]){
            int next = p.first, cost = p.second;
            if(dist[next] != -1) continue;
            dist[next] = dist[pos] + cost;
            q.push(next);
        }
    }

    cout << (*max_element(dist + 1, dist + N + 1));

}
