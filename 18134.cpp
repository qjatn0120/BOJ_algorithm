    #include <bits/stdc++.h>

    using namespace std;

    const int MX = 2005;
    const int inf = 987654321;

    struct Edge{
        int v, cost, cap, rev;
        Edge(int v, int cost, int cap, int rev) : v(v), cost(cost), cap(cap), rev(rev) {}
    };

    struct MinCostMaxFlow{
        vector <Edge> adj[MX];
        int prevV[MX], prevE[MX], dist[MX];
        bool inQ[MX];

        void AddEdge(int s, int e, int cap, int cost){
            adj[s].push_back(Edge(e, cost, cap, (int)adj[e].size()));
            adj[e].push_back(Edge(s, -cost, 0, (int)adj[s].size() - 1));
        }

    pair <int, int> Flow(int S, int E){
        int maxFlow = 0, minCost = 0;
        while(1){
            memset(prevV, -1, sizeof(prevV));
            for(int i = 0; i < MX; i++) dist[i] = inf, inQ[i] = false;

            queue <int> q;
            q.push(S);
            inQ[S] = true;
            dist[S] = 0;
            while(!q.empty()){
                int pos = q.front();
                q.pop();
                inQ[pos] = false;
                for(int e = 0; e < (int)adj[pos].size(); e++){
                    Edge &edge = adj[pos][e];
                    int next = edge.v;
                    if(edge.cap && dist[next] > dist[pos] + edge.cost){
                        dist[next] = dist[pos] + edge.cost;
                        prevV[next] = pos;
                        prevE[next] = e;
                        if(!inQ[next]){
                            q.push(next);
                            inQ[next] = true;
                        }
                    }
                }
            }

            if(prevV[E] == -1) break;

            int flow = inf;
            int pos = E;
            while(pos != S){
                int bef = prevV[pos];
                Edge &edge = adj[bef][prevE[pos]];
                flow = min(flow, edge.cap);
                pos = bef;
            }

            maxFlow += flow;
            pos = E;
            while(pos != S){
                int bef = prevV[pos];
                Edge &edge = adj[bef][prevE[pos]];
                minCost += flow * edge.cost;
                pos = bef;
            }

            pos = E;
            while(pos != S){
                int bef = prevV[pos];
                Edge &edge = adj[bef][prevE[pos]];
                Edge &rev = adj[pos][edge.rev];
                edge.cap -= flow;
                rev.cap += flow;
                pos = bef;
            }
        }
        return make_pair(maxFlow, minCost);
    }
}mcmf;

int N, M, l, u, v, H, T;

int main(){
   cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < M; i++){
        cin >> l >> u >> v;
        mcmf.AddEdge(1000 + u, v, 1, l);
        mcmf.AddEdge(1000 + v, u, 1, l);
    }

    cin >> H >> T;
    for(int i = 1; i <= N; i++){
        if(i == H || i == T) mcmf.AddEdge(i, 1000 + i, 2, 0);
        else mcmf.AddEdge(i, 1000 + i, 1, 0);
    }

    auto res = mcmf.Flow(H, 1000 + T);

    if(res.first == 2) cout << res.second;
    else cout << -1;
}
