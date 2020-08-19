#include <bits/stdc++.h>

using namespace std;

const int MX = 305, inf = 987654321;

struct Edge{
    int v, cap, rev, flow;
    Edge(int v, int cap, int rev, int flow) : v(v), cap(cap), rev(rev), flow(flow) {}
};

struct Dinic{

    vector <Edge> v[MX];
    int Rank[MX], start[MX];

    void addEdge(int s, int e, int c){
        v[s].push_back(Edge(e, c, v[e].size(), 0));
        v[e].push_back(Edge(s, c, v[s].size() - 1, c));
    }

    bool BFS(int S, int E){
        memset(Rank, -1, sizeof(Rank));
        queue <int> q;
        q.push(S), Rank[S] = 0;
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
        for(; start[pos] < v[pos].size(); start[pos]++){
            int i = start[pos];
            int next = v[pos][i].v, cap = v[pos][i].cap - v[pos][i].flow;
            if(Rank[pos] + 1 == Rank[next] && cap){
                int c = DFS(next, E, min(minCap, cap));
                if(c){
                    v[pos][i].flow += c;
                    v[next][v[pos][i].rev].flow -= c;
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

int N, K, D, Z, num;

int main(){
    scanf("%d %d %d", &N, &K, &D);
    for(int i = 1; i <= D; i++){
        scanf("%d", &num);
        nf.addEdge(200 + i, 301, num);
    }
    for(int i = 1; i <= N; i++){
        nf.addEdge(0, i, K);
        scanf("%d", &Z);
        while(Z--) scanf("%d", &num), nf.addEdge(i, 200 + num, 1);
    }
    printf("%d", nf.maxFlow(0, 301));
}
