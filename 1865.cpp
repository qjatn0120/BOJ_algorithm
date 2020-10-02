#include <bits/stdc++.h>

using namespace std;

const int MX = 505;
const int inf = 987654321;

int TC, N, M, W, S, E, T;

vector <pair<int, int> > adj[MX];
int dist[MX];

int main(){
    scanf("%d", &TC);
    while(TC--){
        scanf("%d %d %d", &N, &M, &W);
        for(int i = 1; i <= N; i++) adj[i].clear();
        for(int i = 0; i < M; i++){
            scanf("%d %d %d", &S, &E, &T);
            adj[S].push_back({E, T});
            adj[E].push_back({S, T});
        }
        for(int i = 0; i < W; i++){
            scanf("%d %d %d", &S, &E, &T);
            adj[S].push_back({E, -T});
        }
        fill(dist + 1, dist + N + 1, 0);
        for(int i = 0; i < N - 1; i++){
            for(int st = 1; st <= N; st++){
                for(auto j : adj[st]){
                    int ed = j.first, cost = j.second;
                    dist[ed] = min(dist[ed], dist[st] + cost);
                }
            }
        }
        bool chk = false;
        for(int st = 1; st <= N; st++){
            for(auto i : adj[st]){
                int ed = i.first, cost = i.second;
                if(dist[ed] > dist[st] + cost) chk = true;
            }
        }
        printf("%s\n", chk ? "YES" : "NO");
    }
}
