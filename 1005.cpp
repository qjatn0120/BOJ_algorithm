#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;

vector <int> adj1[MX], adj2[MX];

int T, N, K, X, Y, W, D[MX], t[MX], Left[MX];

void Update(int n);

int main(){
    scanf("%d", &T);
    while(T--){
        for(int i = 0; i < MX; i++) adj1[i].clear(), adj2[i].clear(), t[i] = 0;
        scanf("%d %d", &N, &K);
        for(int i = 1; i <= N; i++) scanf("%d", &D[i]);
        for(int i = 1; i <= K; i++){
            scanf("%d %d", &X, &Y);
            adj1[X].push_back(Y), adj2[Y].push_back(X);
            Left[Y]++;
        }
        scanf("%d", &W);
        queue <int> q;
        for(int i = 1; i <= N; i++){
            if(!Left[i]) q.push(i);
        }
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            Update(pos);
            for(int i = 0; i < adj1[pos].size(); i++){
                int next = adj1[pos][i];
                Left[next]--;
                if(!Left[next]) q.push(next);
            }
        }
        printf("%d\n", t[W]);
    }
}

void Update(int n){
    int t_max = 0;
    for(int i = 0; i < adj2[n].size(); i++){
        int bef = adj2[n][i];
        t_max = max(t_max, t[bef]);
    }
    t[n] = t_max + D[n];
}
