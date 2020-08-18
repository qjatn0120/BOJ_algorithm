#include <bits/stdc++.h>

using namespace std;

const int S = 0, E = 205;
const int MX = 300;
const int inf = 1987654321;

struct Edge{
    Edge(int v, int cap, int rev) : v(v), cap(cap), rev(rev){}
    int v, cap, rev;
};

struct Flow{
    Flow(int v, int flow) : v(v), flow(flow){}
    int v, flow;
};

struct DINIC{
    vector <Edge> v[MX];
    vector <Flow> f[MX];
    int Rank[MX];
    int start[MX];

    void AddEdge(int s, int e, int c){
        v[s].push_back(Edge(e, c, v[e].size()));
        v[e].push_back(Edge(s, c, v[s].size() - 1));
        f[s].push_back(Flow(e, 0));
        f[e].push_back(Flow(s, c));
    }

    bool BFS(){
        queue <int> q;
        for(int i = 0; i < MX; i++) Rank[i] = -1;
        q.push(S);
        Rank[S] = 0;
        while(q.size()){
            int pos = q.front();
            q.pop();
            for(int i = 0; i < v[pos].size(); i++){
                int next = v[pos][i].v;
                int cap = v[pos][i].cap - f[pos][i].flow;
                if(Rank[next] == -1 && cap > 0){
                    Rank[next] = Rank[pos] + 1;
                    q.push(next);
                }
            }
        }
        return Rank[E] != -1;
    }

    int DFS(int pos, int minCap){
        if(pos == E) return minCap;
        for(;start[pos] < v[pos].size(); start[pos]++){
            int next = v[pos][start[pos]].v;
            int cap = v[pos][start[pos]].cap - f[pos][start[pos]].flow;
            if(Rank[pos] + 1 == Rank[next] && cap > 0){
                int c = DFS(next, min(minCap, cap));
                if(c > 0){
                    f[pos][start[pos]].flow += c;
                    f[next][v[pos][start[pos]].rev].flow -= c;
                    return c;
                }

            }
        }
        return 0;
    }

    int maxFlow(){
        int re = 0;
        while(BFS()){
            for(int i = 0; i < MX; i++) start[i] = 0;
            while(1){
                int tmp = DFS(S, inf);
                if(!tmp) break;
                re += tmp;
            }
        }
        return re;
    }
}Dinic;

int N, M, a, b;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) Dinic.AddEdge(S, i, 1);
    for(int i = 1; i <= N; i++) Dinic.AddEdge(100 + i, E, 1);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a ,&b);
        Dinic.AddEdge(a, 100 + b, 1);
    }
    printf("%d", Dinic.maxFlow());
}
