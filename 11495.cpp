#include <bits/stdc++.h>

using namespace std;

const int MX = 3000;
const int inf = 1987654321;

struct Edge{
    Edge(int v, int cap, int rev, int flow) : v(v), cap(cap), rev(rev), flow(flow) {}
    int v, cap, rev, flow;
};

struct Dinic{
    vector <Edge> v[MX];
    int Rank[MX], start[MX];

    void Clear(){
        for(int i = 0; i < MX; i++) v[i].clear();
    }

    void AddEdge(int s, int e, int c){
        v[s].push_back({e, c, v[e].size(), 0});
        v[e].push_back({s, c, v[s].size() - 1, c});
    }

    bool BFS(int S, int E){
        queue <int> q;
        for(int i = 0; i < MX; i++) Rank[i] = -1;
        Rank[S] = 0;
        q.push(S);
        while(q.size()){
            int pos = q.front();
            q.pop();
            for(int i = 0; i < v[pos].size(); i++){
                int next = v[pos][i].v;
                if(Rank[next] == -1 && v[pos][i].cap != v[pos][i].flow){
                    Rank[next] = Rank[pos] + 1;
                    q.push(next);
                }
            }
        }
        return Rank[E] != -1;
    }

    int DFS(int pos, int E, int minCap){
        if(pos == E) return minCap;
        for(;start[pos] < v[pos].size(); start[pos]++){
            int next = v[pos][start[pos]].v;
            int cap = v[pos][start[pos]].cap - v[pos][start[pos]].flow;
            if(Rank[pos] + 1 == Rank[next] && cap){
                int c = DFS(next, E, min(minCap, cap));
                if(c){
                    v[pos][start[pos]].flow += c;
                    v[next][v[pos][start[pos]].rev].flow -= c;
                    return c;
                }
            }
        }
        return 0;
    }

    int maxFlow(int S, int E){
        int ret = 0;
        while(BFS(S, E)){
            for(int i = 0; i < MX; i++) start[i] = 0;
            while(1){
                int tmp = DFS(S, E, inf);
                if(!tmp) break;
                ret += tmp;
            }
        }
        return ret;
    }
}NF;

const int dir_x[4] = {0, 1, 0, -1};
const int dir_y[4] = {1, 0, -1, 0};

int T, n, m, ans;
int arr[55][55];

int main(){
    scanf("%d", &T);
    while(T--){
        NF.Clear();
        ans = 0;
        scanf("%d %d", &n, &m);
        for(int j = 0; j < n; j++)
        for(int i = 0; i < m; i++) scanf("%d", &arr[i][j]), ans += arr[i][j];
        for(int j = 0; j < n; j++)
        for(int i = 0; i < m; i++){
            if((i + j) & 1){
                NF.AddEdge(2500, i + j * m, arr[i][j]);
                for(int dir = 0; dir < 4; dir++){
                    int x = i + dir_x[dir];
                    int y = j + dir_y[dir];
                    if(x < 0 || x >= m || y < 0 || y >= n) continue;
                    NF.AddEdge(i + j * m, x + y * m, 10000);
                }
            }else{
                NF.AddEdge(i + j * m, 2501, arr[i][j]);
            }
        }
        printf("%d\n", ans - NF.maxFlow(2500, 2501));
    }
}
