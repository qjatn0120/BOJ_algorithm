#include <bits/stdc++.h>

using namespace std;

const int MX = 2005;
const int inf = 987654320;

int T, n, m, t, s, g, h, a, b, d, x, dist[MX], bef[MX];
priority_queue <pair<int, int> > pq;
vector <int> X, ans;
vector <pair<int, int> > adj[MX];

int main(){
    scanf("%d", &T);
    while(T--){
        for(int i = 0; i < MX; i++) adj[i].clear();
        X.clear();
        ans.clear();
        scanf("%d %d %d", &n, &m, &t);
        scanf("%d %d %d", &s, &g, &h);
        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &a, &b, &d);
            if((a == g && b == h) || (a == h && b == g)) d = d * 2 - 1;
            else d = d * 2;
            adj[a].push_back({b, d});
            adj[b].push_back({a, d});
        }
        for(int i = 0; i < t; i++) scanf("%d", &x), X.push_back(x);
        for(int i = 0; i < MX; i++) dist[i] = inf, bef[i] = false;
        dist[s] = 0;
        pq.push({0, s});
        while(pq.size()){
            pair <int, int> tmp = pq.top();
            pq.pop();
            int pos = tmp.second;
            int Dist = -tmp.first;
            if(Dist != dist[pos]) continue;
            for(int i = 0; i < adj[pos].size(); i++){
                int nextPos = adj[pos][i].first;
                int nextDist = Dist + adj[pos][i].second;
                if(dist[nextPos] > nextDist){
                    dist[nextPos] = nextDist;
                    pq.push({-nextDist, nextPos});
                }
            }
        }
        for(int i = 0; i < X.size(); i++){
            if(dist[X[i]] & 1) ans.push_back(X[i]);
        }
        sort(ans.begin(), ans.end());
        for(int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
        printf("\n");
    }
}
