#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

vector <pair<int, int> > adj[MX];
vector <int> child[MX];

int N, K, A, B, C, cnt[MX], dist[MX];
bool del[MX], visited[MX], visited2[MX];

void makeTree(int n){
    visited[n] = true;
    cnt[n] = 1;
    child[n].clear();
    for(auto i : adj[n]){
        int next = i.first;
        if(del[next] || visited[next]) continue;
        child[n].push_back(next);
        makeTree(next);
        cnt[n] += cnt[next];
    }
}

int getCent(int n){
    int ret = n;
    bool chk = true;
    while(chk){
        chk = false;
        for(int next : child[ret]){
            if(!del[next] && cnt[next] > cnt[n] / 2){
                ret = next;
                chk = true;
            }
        }
    }
    return ret;
}

void BFS(int n){
    queue <int> q;
    q.push(n);
    visited2[n] = true;
    dist[n] = cnt[n] = 0;
    while(!q.empty()){
        int pos = q.front();
        child[pos].clear();
        q.pop();
        for(auto i : adj[pos]){
            int next = i.first, cost = i.second;
            if(visited2[next] || del[next]) continue;
            cnt[next] = cnt[pos] + 1;
            dist[next] = dist[pos] + cost;
            visited2[next] = true;
            child[pos].push_back(next);
            q.push(next);
        }
    }
}

int getAns(int n){
    map <int, int> mp;
    mp[0] = 0;
    int ret = MX;
    for(int tar : child[n]){
        queue <int> q;
        q.push(tar);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            if(mp.find(K - dist[pos]) != mp.end()) ret = min(ret, mp[K - dist[pos]] + cnt[pos]);
            for(int next : child[pos]) q.push(next);
        }
        q.push(tar);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            auto result = mp.insert({dist[pos], cnt[pos]});
            if(!result.second) result.first->second = min(result.first->second, cnt[pos]);
            for(int next : child[pos]) q.push(next);
        }
    }
    return ret;
}

int main(){
    scanf("%d %d", &N, &K);
    for(int i = 0; i < N - 1; i++){
        scanf("%d %d %d", &A, &B, &C);
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }
    int ans = MX;
    int rep = N;
    while(rep){
        memset(visited, 0, sizeof(visited)), memset(visited2, 0, sizeof(visited2));
        for(int i = 0; i < N; i++){
            if(!del[i] && !visited[i]){
                makeTree(i);
                int tar = getCent(i);
                BFS(tar);
                ans = min(ans, getAns(tar));
                del[tar] = true;
                rep--;
            }
        }
    }
    printf("%d", ans == MX ? -1 : ans);
}

