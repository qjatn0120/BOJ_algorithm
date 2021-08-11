#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

bool visited[MX];
int N, a, b;
long long int h[MX], sz[MX], ans;
vector <int> adj[MX], child[MX];

void DFS(int pos){
    visited[pos] = true;
    sz[pos] = 1;
    for(int next : adj[pos]){
        if(visited[next]) continue;
        h[next] = h[pos] + 1;
        child[pos].push_back(next);
        DFS(next);
        sz[pos] += sz[next];
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);

    cin >> N;
    for(int i = 0; i < N - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    DFS(1);

    for(int i = 1; i <= N; i++) ans += h[i] * (N - 1);
    for(int i = 1; i <= N; i++){
        ans -= (sz[i] * (sz[i] - 1)) / 2 * h[i];
        for(int c : child[i]) ans += (sz[c] * (sz[c] - 1)) / 2 * h[i];
    }

    cout << ans;
}
