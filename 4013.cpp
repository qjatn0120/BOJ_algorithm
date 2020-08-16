#include <bits/stdc++.h>

using namespace std;

const int MX = 500005;

struct StronglyConnectedComponent{

    vector <int> adj[MX];
    vector <int> rev[MX];
    vector <vector<int> > SCC;
    bool visited[MX];
    stack <int> st;

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

    void DFS2(int n, vector <int>& v){
        v.push_back(n);
        visited[n] = true;
        for(int i = 0; i < (int)rev[n].size(); i++){
            int next = rev[n][i];
            if(visited[next]) continue;
            DFS2(next, v);
        }
    }

    void calSCC(int SIZE){
        for(int i = 1; i <= SIZE; i++) visited[i] = false;
        for(int i = 1; i <= SIZE; i++){
            if(!visited[i]) DFS(i);
        }
        for(int i = 1; i <= SIZE; i++) visited[i] = false;
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

int n, N, M, S, P, a, b;
int price[MX];
int target[MX], newNode[MX];
long long int maxPrice[MX], priceNew[MX];
int bef[MX];
bool isTarget[MX];
vector <int> adj[MX];

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        SCC.AddEdge(a, b);
    }
    for(int i = 1; i <= N; i++) scanf("%d", &price[i]);
    scanf("%d %d", &S, &P);
    for(int i = 0; i < P; i++) scanf("%d", &target[i]);
    SCC.calSCC(N);
    n = (int)SCC.SCC.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (int)SCC.SCC[i].size(); j++){
            newNode[SCC.SCC[i][j]] = i;
        }
    }
    for(int i = 1; i <= N; i++) priceNew[newNode[i]] += price[i];
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < (int)SCC.adj[i].size(); j++){
            a = i, b = SCC.adj[i][j];
            a = newNode[a], b = newNode[b];
            if(a == b) continue;
            adj[a].push_back(b);
        }
    }
    S = newNode[S];
    for(int i = 0; i < P; i++) isTarget[newNode[target[i]]] = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < (int)adj[i].size(); j++){
            bef[adj[i][j]]++;
        }
    }
    queue <int> q;
    for(int i = 0; i < n; i++){
        if(!bef[i]) q.push(i);
    }

    for(int i = 0; i < n; i++) maxPrice[i] = -LONG_LONG_MAX / 10;
    maxPrice[S] = priceNew[S];

    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(int i = 0; i < (int)adj[pos].size(); i++){
            int next = adj[pos][i];
            maxPrice[next] = max(maxPrice[next], maxPrice[pos] + priceNew[next]);
            bef[next]--;
            if(!bef[next]) q.push(next);
        }
    }

    long long int ans = 0;
    for(int i = 0; i < n; i++){
        if(isTarget[i]) ans = max(ans, maxPrice[i]);
    }
    printf("%lld", ans);
}
