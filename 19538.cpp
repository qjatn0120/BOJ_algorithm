#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

vector <int> adj[MX];

int N, M, tmp, visited[MX], cnt[MX];

int main(){
    memset(visited, -1, sizeof(visited));
    scanf("%d", &N);
    for(int i = 1; i <= N; i++){
        while(1){
            scanf("%d", &tmp);
            if(!tmp) break;
            adj[i].push_back(tmp);
        }
    }
    scanf("%d", &M);
    queue <int> q;
    for(int i = 0; i < M; i++){
        scanf("%d", &tmp);
        visited[tmp] = 0;
        q.push(tmp);
    }

    while(q.size()){
        int pos = q.front();
        q.pop();
        for(int next : adj[pos]){
            if(visited[next] != -1) continue;
            cnt[next]++;
            if(cnt[next] * 2 >= (int)adj[next].size()){
                visited[next] = visited[pos] + 1;
                q.push(next);
            }
        }
    }
    for(int i = 1; i <= N; i++) printf("%d ", visited[i]);
}
