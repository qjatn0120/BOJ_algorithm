#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

int V;

struct ArticulationPoint{
    vector <int> adj[MX];
    int disc[MX], idx;
    bool cut[MX];

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int pos, bool root){
        int ret = disc[pos] = ++idx;
        int child = 0;
        for(int &next : adj[pos]){
            if(!disc[next]){
                child++;
                int res = dfs(next, false);
                if(!root && res >= disc[pos]) cut[pos] = true;
                ret = min(ret, res);
            }else ret = min(ret, disc[next]);
        }

        if(root && child > 1) cut[pos] = true;

        return ret;
    }

    void getAP(){
        for(int i = 1; i <= V; i++) disc[i] = 0, cut[i] = false;
        idx = 0;
        for(int i = 1; i <= V; i++){
            if(!disc[i]) dfs(i, true);
        }
    }
}ap;

int N, M, a, b;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    V = N;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        ap.addEdge(a, b);
    }

    ap.getAP();

    vector <int> ans;
    for(int i = 1; i <= N; i++){
        if(ap.cut[i]) ans.push_back(i);
    }

    cout << (int)ans.size() << "\n";
    for(int i : ans) cout << i << " ";
}
