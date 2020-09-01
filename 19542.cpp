#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;

int N, S, D, x, y, h[MX];
bool visited[MX];

vector <int> adj[MX];

void makeTree(int n){
    h[n] = 0;
    visited[n] = true;
    for(int next : adj[n]){
        if(!visited[next]){
            makeTree(next);
            h[n] = max(h[n], h[next] + 1);
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &S, &D);
    for(int i = 0; i < N - 1; i++){
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    makeTree(S);
    int ans = 0;
    for(int i = 1; i <= N; i++){
        if(i == S) continue;
        if(h[i] >= D) ans++;
    }
    printf("%d", ans * 2);
}
