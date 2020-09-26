#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

int N, M, A, B, C, S, E;

vector <pair<int, int> > adj[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    cin >> S >> E;
    bool visited[MX];
    int lo = 1, hi = 1e9;
    while(lo < hi){
        int mid = lo + hi + 1 >> 1;
        memset(visited, 0, sizeof(visited));
        queue <int> q;
        q.push(S);
        visited[S] = true;
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            for(auto i : adj[pos]){
                int next = i.first, cost = i.second;
                if(visited[next] || cost < mid) continue;
                q.push(next);
                visited[next] = true;
            }
        }
        if(visited[E]) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}
