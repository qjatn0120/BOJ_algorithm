#include <bits/stdc++.h>

using namespace std;

const int S = 0, E = 105;
const int MX = 150, inf = 1987654321;

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

    void Clear(){
        for(int i = 0; i < MX; i++) v[i].clear(), f[i].clear();
    }

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

bool isPrime(int a);

int N, tmp;
vector <int> num, ans, v1, v2;

int main(){
    scanf("%d", &N);
    for(int i  = 0; i < N; i++){
        scanf("%d", &tmp);
        num.push_back(tmp);
    }
    for(int i = 1; i < N; i++){
        if(!isPrime(num[0] + num[i])) continue;
        v1.clear();
        v2.clear();
        for(int j = 1; j < N; j++){
            if(i == j) continue;
            if(num[j] % 2 == 0) v1.push_back(num[j]);
            else v2.push_back(num[j]);
        }
        Dinic.Clear();
        for(int i = 1; i <= v1.size(); i++) Dinic.AddEdge(S, i, 1);
        for(int i = 1; i <= v2.size(); i++) Dinic.AddEdge(50 + i, E, 1);
        for(int i = 0; i < v1.size(); i++){
            for(int j = 0; j < v2.size(); j++){
                if(isPrime(v1[i] + v2[j])) Dinic.AddEdge(1 + i, 51 + j, 1);
            }
        }
        int matched = Dinic.maxFlow();
        if(matched * 2 + 2 == N) ans.push_back(num[i]);
    }
    sort(ans.begin(), ans.end());
    if(ans.size()){
        for(int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
    }else{
        printf("-1");
    }
}

bool isPrime(int a){
    for(int i = 2; i * i <= a; i++){
        if(a % i == 0) return false;
    }
    return true;
}
