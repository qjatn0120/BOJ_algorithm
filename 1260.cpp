#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;

int N, M, V, A, B;
bool visited[MX];
vector <int> adj[MX];

void DFS(int pos){
    visited[pos] = true;
    cout << pos << " ";
    for(int next : adj[pos]){
        if(visited[next]) continue;
        DFS(next);
    }
}

void BFS(int pos){
    queue <int> q;
    q.push(pos);
    visited[pos] = true;
    while(!q.empty()){
        int p = q.front();
        cout << p << " ";
        q.pop();
        for(int next : adj[p]){
            if(visited[next]) continue;
            q.push(next);
            visited[next] = true;
        }
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M >> V;
    for(int i = 0; i < M; i++){
        cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    for(int i = 1; i <= N; i++) sort(adj[i].begin(), adj[i].end());
    memset(visited, 0, sizeof(visited));
    DFS(V);
    cout << "\n";
    memset(visited, 0, sizeof(visited));
    BFS(V);
}
