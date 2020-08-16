#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;

struct StronglyConnectecComponent{

    vector <int> adj[MX];
    vector <int> rev[MX];
    bool visited[MX];

    stack <int> st;
    vector <vector<int> > SCC;

    void Clear(){
        for(int i = 0; i < MX; i++) adj[i].clear(), rev[i].clear();
        SCC.clear();
    }

    void addEdge(int a, int b){
        adj[a].push_back(b);
        rev[b].push_back(a);
    }

    void DFS(int n){
        visited[n] = true;
        for(int i = 0; i < adj[n].size(); i++){
            int next = adj[n][i];
            if(visited[next]) continue;
            DFS(next);
        }
        st.push(n);
    }

    void DFS2(int n, vector <int>& v){
        visited[n] = true;
        v.push_back(n);
        for(int i = 0; i < rev[n].size(); i++){
            int next = rev[n][i];
            if(visited[next]) continue;
            DFS2(next, v);
        }
    }

    void calcSCC(int SIZE){
        for(int i = 0; i < SIZE; i++) visited[i] = false;
        for(int i = 0; i < SIZE; i++){
            if(!visited[i]) DFS(i);
        }
        for(int i = 0; i < SIZE; i++) visited[i] = false;
        while(!st.empty()){
            int tar = st.top();
            st.pop();
            if(visited[tar]) continue;
            vector <int> v;
            DFS2(tar, v);
            SCC.push_back(v);
        }
    }

}SCC;

int t, N, M, A, B;
int newNode[MX];
int bef[MX];

int main(){
    scanf("%d", &t);
    while(t--){
        SCC.Clear();
        scanf("%d %d", &N, &M);
        for(int i = 0; i < M; i++){
            scanf("%d %d", &A, &B);
            SCC.addEdge(A, B);
        }
        SCC.calcSCC(N);
        for(int i = 0; i < SCC.SCC.size(); i++){
            for(int j = 0; j < SCC.SCC[i].size(); j++){
                newNode[SCC.SCC[i][j]] = i;
            }
        }
        for(int i = 0; i < SCC.SCC.size(); i++) bef[i] = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < SCC.adj[i].size(); j++){
                int a = newNode[i], b = newNode[SCC.adj[i][j]];
                if(a == b) continue;
                bef[b]++;
            }
        }
        int cnt = 0, ans;
        for(int i = 0; i < SCC.SCC.size(); i++){
            if(bef[i] == 0) cnt++, ans = i;
        }
        if(cnt == 1){
            sort(SCC.SCC[ans].begin(), SCC.SCC[ans].end());
            for(int i = 0; i < SCC.SCC[ans].size(); i++) printf("%d\n", SCC.SCC[ans][i]);
        }else printf("Confused\n");
        printf("\n");
    }
}
