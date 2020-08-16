#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

struct Query{
    bool type;
    int a, b;

    Query(int a, int b) : type(true), a(a), b(b) {}
    Query(int a) : type(false), a(a) {}
};

int N, Q, a, b, dest[MX], adj[MX];
bool isCycle[MX];

int findDest(int a){if(a == dest[a]) return a; return dest[a] = findDest(dest[a]);}

vector <Query> query;
vector <int> ans;

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &adj[i]);
    for(int i = 1; i <= N; i++) dest[i] = i;
    scanf("%d", &Q);
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &a, &b);
        if(a == 1) query.push_back(Query(b));
        else query.push_back(Query(b, adj[b])), adj[b] = 0;
    }
    for(int i = 1; i <= N; i++){
        if(adj[i]) query.push_back(Query(i, adj[i])), adj[i] = 0;
    }
    reverse(query.begin(), query.end());
    for(int i = 0; i < query.size(); i++){
        if(query[i].type){
            a = query[i].a, b = query[i].b;
            b = findDest(b);
            if(a == dest[b]) isCycle[a] = true;
            else dest[a] = dest[b];
        }else{
            a = query[i].a;
            dest[a] = findDest(a);
            if(isCycle[dest[a]]) ans.push_back(-1);
            else ans.push_back(dest[a]);
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto i : ans){
        if(i == -1) printf("CIKLUS\n");
        else printf("%d\n", i);
    }
}
