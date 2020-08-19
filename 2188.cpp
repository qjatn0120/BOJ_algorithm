#include <bits/stdc++.h>

using namespace std;

const int MX = 505;
const int inf = 987654321;

struct Edge{
    int v, cap, rev, flow;
    Edge(int v, int cap, int rev, int flow) : v(v), cap(cap), rev(rev), flow(flow) {}
};

struct Dinic{

    vector <Edge> v[MX];
    int Rank[MX], start[MX];

    void addEdge(int a, int b, int c){
        v[a].push_back(Edge(b, c, v[b].size(), 0));
        v[b].push_back(Edge(a, c, v[a].size() - 1, c));
    }

    bool BFS(int S, int E){
        memset(Rank, -1, sizeof(Rank));
        queue <int> q;
        Rank[S] = 0, q.push(S);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            for(auto i : v[pos]){
                int next = i.v, cap = i.cap - i.flow;
                if(Rank[next] == -1 && cap){
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
            memset(start, 0, sizeof(start));
            while(1){
                int tmp = DFS(S, E, inf);
                if(!tmp) break;
                ret += tmp;
            }
        }
        return ret;
    }

}nf;

int N, M, a, b;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++){
        scanf("%d", &a);
        while(a--) scanf("%d", &b), nf.addEdge(i, b + 200, 1);
    }
    for(int i = 1; i <= N; i++) nf.addEdge(0, i, 1);
    for(int i = 1; i <= M; i++) nf.addEdge(i + 200, 401, 1);
    printf("%d", nf.maxFlow(0, 401));
}
