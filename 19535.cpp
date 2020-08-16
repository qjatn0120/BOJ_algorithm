#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

struct Node{
    vector <int> child;
    int par;
    long long int cnt[4];

    Node(){
        cnt[0] = 1, cnt[1] = cnt[2] = cnt[3] = 0;
        par = -1;
    }
};

struct Tree{

    bool visited[MX];
    vector <int> adj[MX];
    Node node[MX];

    Tree(){
        for(int i = 0; i < MX; i++) visited[i] = false;
    }

    void addEdge(int a, int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    void makeTree(int n){
        visited[n] = true;
        for(int i = 0; i < (int)adj[n].size(); i++){
            int next = adj[n][i];
            if(visited[next]) continue;
            node[n].child.push_back(next);
            node[next].par = n;
            makeTree(next);
            for(int j = 1; j < 4; j++) node[n].cnt[j] += node[next].cnt[j - 1];
        }
    }

    long long int calD(int n){
        long long int ret = 0;
        for(int next : node[n].child){
            ret += (node[n].cnt[1] - 1) * node[next].cnt[1];
            ret += calD(next);
        }
        ret += node[n].cnt[3];
        return ret;
    }

    long long int calG(int n){
        long long int ret = 0;
        if(node[n].par != -1) ret += (node[n].cnt[1] * (node[n].cnt[1] - 1)) / 2;
        ret += (node[n].cnt[1] * (node[n].cnt[1] - 1) * (node[n].cnt[1] - 2)) / 6;
        for(int next : node[n].child) ret += calG(next);
        return ret;
    }

}tree;

int N, u, v;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N - 1; i++) scanf("%d %d", &u, &v), tree.addEdge(u, v);
    tree.makeTree(1);
    long long int D = tree.calD(1), G = tree.calG(1) * 3;
    if(D == G) printf("DUDUDUNGA");
    else if(D > G) printf("D");
    else printf("G");
}
