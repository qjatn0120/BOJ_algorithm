#include <bits/stdc++.h>

using namespace std;

// MAX Edge
const int MX = 1e5 + 5;

int V;

struct ArticulationEdge{
    vector <pair<int, int> > edge;
    vector <bool> cut;
    vector <pair<int, int> > adj[MX];
    int disc[MX], idx;

    void addEdge(int u, int v){
        adj[u].push_back(make_pair(v, (int)edge.size()));
        adj[v].push_back(make_pair(u, (int)edge.size()));
        edge.push_back(make_pair(u, v));
        cut.push_back(false);
    }

    int dfs(int pos, int bef){
        int ret = disc[pos] = ++idx;
        for(auto &e : adj[pos]){
            int next = e.first, eidx = e.second;
            if(next == bef) continue;
            if(!disc[next]){
                int res = dfs(next, pos);
                if(res > disc[pos]) cut[eidx] = true;
                ret = min(res, ret);
            }else ret = min(ret, disc[next]);
        }

        return ret;
    }

    void getAE(){
        for(int i = 1; i <= V; i++) disc[i] = 0;
        idx = 0;
        for(int i = 1; i <= V; i++){
            if(!disc[i]) dfs(i, -1);
        }
    }

}ae;

int N, M, a, b;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    V = N;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        ae.addEdge(a, b);
    }

    ae.getAE();

    vector <pair<int, int> > ans;

    for(int i = 0; i < M; i++){
        if(ae.cut[i]) ans.push_back(make_pair(min(ae.edge[i].first, ae.edge[i].second), max(ae.edge[i].first, ae.edge[i].second)));
    }

    sort(ans.begin(), ans.end());

    cout << (int)ans.size() << "\n";
    for(auto &e : ans) cout << e.first << " " << e.second << "\n";
}