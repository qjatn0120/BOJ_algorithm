#include <bits/stdc++.h>

using namespace std;

const int MX = 5e4 + 5;
const int inf = 987654321;

vector <pair<int, int> > mst[MX];//adj of MST, and others
vector <tuple<int, int, int> > adj, adj1;

int V, E, A, B, C, tmp[4], h[MX], group[MX], par[MX][17], maxCost[MX][17], secCost[MX][17];
long long int MSTcost;

int Find(int a){if(a == group[a]) return a; return group[a] = Find(group[a]);}

void Union(int a, int b){
    a = Find(a), b = Find(b);
    group[a] = b;
}

int getLCA(int p, int q){
    if(h[p] < h[q]) swap(p, q);
    int gap = h[p] - h[q];
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            gap ^= (1 << i);
            p = par[p][i];
        }
    }
    if(p == q) return p;
    for(int i = 16; i >= 0; i--){
        if(par[p][i] != par[q][i]) p = par[p][i], q = par[q][i];
    }
    return par[p][0];
}

int getMax(int p, int c){
    int gap = h[c] - h[p];
    int ret = -1;
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            gap ^= (1 << i);
            ret = max(ret, maxCost[c][i]);
            c = par[c][i];
        }
    }
    return ret;
}

pair<int, int> getSecond(int p, int c){
    int MAX = -1, sec = -1;
    int gap = h[c] - h[p];
    for(int i = 0; gap; i++){
        if(gap & (1 << i)){
            gap ^= (1 << i);
            tmp[0] = MAX;
            tmp[1] = sec;
            tmp[2] = maxCost[c][i];
            tmp[3] = secCost[c][i];
            sort(tmp, tmp + 4);
            MAX = tmp[3];
            for(int k = 2; k >= 0; k--){
                if(tmp[k] != tmp[k + 1]){
                    sec = tmp[k];
                    break;
                }
            }
            c = par[c][i];
        }
    }
    return make_pair(MAX, sec);
}

int main(){
    scanf("%d %d", &V, &E);
    iota(group + 1, group + V + 1, 1);
    for(int i = 0; i < E; i++){
        scanf("%d %d %d", &A, &B, &C);
        adj.push_back({C, A, B});
    }
    sort(adj.begin(), adj.end());
    int cnt = 0;
    for(auto i : adj){
        int cost = get<0>(i), p = get<1>(i), q = get<2>(i);
        if(Find(p) == Find(q)) adj1.push_back(i);
        else Union(p, q), mst[p].push_back({q, cost}), mst[q].push_back({p, cost}), MSTcost += cost, cnt++;
    }
    if(cnt != V - 1){
        printf("-1");
        return 0;
    }
    bool visited[MX] = {};
    queue <int> q;
    q.push(1);
    visited[1] = true;
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(auto i : mst[pos]){
            int next = i.first, cost = i.second;
            if(!visited[next]){
                par[next][0] = pos;
                maxCost[next][0] = cost;
                h[next] = h[pos] + 1;
                visited[next] = true;
                q.push(next);
            }
        }
    }
    maxCost[1][0] = -1, par[1][0] = 1;
    for(int i = 1; i <= V; i++) secCost[i][0] = -1;
    for(int j = 1; j < 17; j++)
    for(int i = 1; i <= V; i++){
        par[i][j] = par[par[i][j - 1]][j - 1];
        maxCost[i][j] = max(maxCost[i][j - 1], maxCost[par[i][j - 1]][j - 1]);
        tmp[0] = maxCost[i][j - 1];
        tmp[1] = maxCost[par[i][j - 1]][j - 1];
        tmp[2] = secCost[i][j - 1];
        tmp[3] = secCost[par[i][j - 1]][j - 1];
        sort(tmp, tmp + 4);
        for(int k = 2; k >= 0; k--){
            if(tmp[k] != tmp[k + 1]){
                secCost[i][j] = tmp[k];
                break;
            }
        }
    }
    int ans = inf;
    for(auto i : adj1){
        int c = get<0>(i), p = get<1>(i), q = get<2>(i);
        int par = getLCA(p, q);
        int temp = max(getMax(par, p), getMax(par, q));
        if(temp == c){
            auto j1 = getSecond(par, p), j2 = getSecond(par, q);
            tmp[0] = j1.first, tmp[1] = j1.second, tmp[2] = j2.first, tmp[3] = j2.second;
            sort(tmp, tmp + 4);
            for(int k = 2; k >= 0; k--){
                if(tmp[k] != tmp[k + 1]){
                    temp = tmp[k];
                    break;
                }
            }
            if(temp != -1) ans = min(ans, c - temp);
        }else ans = min(ans, c - temp);
    }
    if(ans == inf) printf("-1");
    else printf("%lld", MSTcost + ans);
}