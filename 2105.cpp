#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;
const int inf = 987654321;

vector <pair<int, int> > query;
vector <int> adj[MX];
pair <int, int> child[MX];
int N, M, a, b, t[MX];
void addEdge(int a, int b);
void DFS(int p, int num);

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) scanf("%d %d", &child[i].first, &child[i].second);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        if(b == 1){
            query.push_back({a, child[a].first});
            child[a].first = -1;
        }else{
            query.push_back({a, child[a].second});
            child[a].second = -1;
        }
    }
    for(int i = 1; i <= N; i++) t[i] = inf;
    for(int i = 1; i <= N; i++){
        if(child[i].first != -1) addEdge(i, child[i].first);
        if(child[i].second != -1) addEdge(i, child[i].second);
    }
    DFS(1, -1);
    for(int i = M - 1; i >= 0; i--){
        a = query[i].first, b = query[i].second;
        addEdge(a, b);
        if(t[a] == inf && t[b] != inf) DFS(a, i);
        else if(t[a] != inf && t[b] == inf) DFS(b, i);
    }
    for(int i = 1; i <= N; i++) printf("%d\n", t[i]);
}

void addEdge(int a, int b){
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void DFS(int p, int num){
    t[p] = num;
    for(int i = 0; i < adj[p].size(); i++){
        int next = adj[p][i];
        if(t[next] == inf) DFS(next, num);
    }
}
