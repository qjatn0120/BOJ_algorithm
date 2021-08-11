#include <bits/stdc++.h>

using namespace std;

const int MX = 55;

struct circle{
    pair<int, int> p;
    int r;
    circle(pair<int, int> p, int r): p(p), r(r) {}
};

bool isIn(circle a, circle b){//a가 b안에 있는지를 검사
    int dx = a.p.first - b.p.first;
    int dy = a.p.second - b.p.second;
    return dx * dx + dy * dy < (b.r - a.r) * (b.r - a.r);
}

bool isIn(circle a, pair<int, int> p){//점 p가 원 a안에 있느지를 검사
    int dx = a.p.first - p.first;
    int dy = a.p.second - p.second;
    return dx * dx + dy * dy < a.r * a.r;
}

struct Graph{

    vector <int> adj[MX];
    int dist[MX];
    bool visited[MX];

    void Clear(){
        for(int i = 0; i < MX; i++) adj[i].clear(), visited[i] = 0, dist[i] = -1;
    }

    void AddEdge(int a, int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int calDist(int a, int b){
        queue <int> q;
        dist[a] = 0;
        q.push(a);
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            for(int i = 0; i < adj[pos].size(); i++){
                int next = adj[pos][i];
                if(dist[next] != -1) continue;
                q.push(next);
                dist[next] = dist[pos] + 1;
            }
        }
        return dist[b];
    }
}graph;

int cmp(circle a, circle b){return a.r < b.r;}

vector <circle> Circle;

int X1, Y1, X2, Y2, cx, cy, r, n, T;

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        scanf("%d", &n);
        graph.Clear();
        Circle.clear();
        for(int i = 0; i < n; i++){
            scanf("%d %d %d", &cx, &cy, &r);
            Circle.push_back(circle(make_pair(cx, cy), r));
        }
        sort(Circle.begin(), Circle.end(), cmp);
        for(int i = 0; i < n; i++){
            bool inCircle = false;
            for(int j = i + 1; j < n; j++){
                if(isIn(Circle[i], Circle[j])){
                    graph.AddEdge(i, j);
                    inCircle = true;
                    break;
                }
            }
            if(!inCircle) graph.AddEdge(i, 50);
        }
        int p1 = 50, p2 = 50;
        for(int i = 0; i < n; i++){
            if(isIn(Circle[i], make_pair(X1, Y1))){
                p1 = i;
                break;
            }
        }
        for(int i = 0; i < n; i++){
            if(isIn(Circle[i], make_pair(X2, Y2))){
                p2 = i;
                break;
            }
        }
        printf("%d\n", graph.calDist(p1, p2));
    }
}
