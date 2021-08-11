#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;
int V;

bool cmp(vector <int> v1, vector <int> v2){
    return v1[0] < v2[0];
}

struct StronglyConnectedComponent{

    vector <int> adj[MX], rev[MX];
    stack <int> st;
    vector <vector <int> > SCC;

    bool visited[MX] = {};

    void AddEdge(int a, int b){
        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    void DFS(int n){
        visited[n] = true;
        for(int i = 0; i < (int)adj[n].size(); i++){
            int next = adj[n][i];
            if(visited[next]) continue;
            DFS(next);
        }
        st.push(n);
    }

    void DFS2(int n, vector <int> &v){
        visited[n] = true;
        v.push_back(n);
        for(int i = 0; i < (int)rev[n].size(); i++){
            int next = rev[n][i];
            if(visited[next]) continue;
            DFS2(next, v);
        }
    }

    void calSCC(){
        for(int i = 1; i <= V; i++){
            if(visited[i]) continue;
            DFS(i);
        }
        for(int i = 0; i < MX; i++) visited[i] = false;
        while(!st.empty()){
            int tar = st.top();
            st.pop();
            if(visited[tar]) continue;
            vector <int> tmp;
            DFS2(tar, tmp);
            SCC.push_back(tmp);
        }
    }

}SCC;

bool chk[MX];
int N, M, x, y, bef[MX], group[MX];
vector <pair<int, int> > adj;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    V = N;
    for(int i = 0; i < M; i++){
        cin >> x >> y;
        chk[x] = chk[y] = true;
        SCC.AddEdge(x, y);
        adj.push_back(make_pair(x, y));
    }
    SCC.calSCC();

    for(int i = 0; i < SCC.SCC.size(); i++){
        for(int v : SCC.SCC[i]) group[v] = i;
    }

    for(auto p : adj){
        int g1 = group[p.first], g2 = group[p.second];
        if(g1 == g2) continue;
        bef[g2]++;
    }

    int ans = 0;

    for(int g = 0; g < SCC.SCC.size(); g++){
        if(!bef[g]) ans++;
    }

    cout << ans;

}
