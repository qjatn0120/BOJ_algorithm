#include <bits/stdc++.h>

using namespace std;

struct Point{
    long long int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator == (Point &r){
        return r.x == x && r.y == y;
    }

};

int CCW(Point p, Point q, Point r){
    long long int c = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    if(c > 0) return 1;
    if(c < 0) return -1;
    return 0;
}

bool isOverlap(Point p1, Point p2, Point q1, Point q2){
    if(CCW(p1, p2, q1) * CCW(p1, p2, q2) < 0 && CCW(q1, q2, p1) * CCW(q1, q2, p2) < 0) return true;
    if(CCW(p1, p2, q2) == 0 && CCW(q1, q2, p1) * CCW(q1, q2, p2) < 0) return true;
    if(CCW(q1, q2, p2) == 0 && CCW(p1, p2, q1) * CCW(p1, p2, q2) < 0) return true;
    if(p2 == q2) return true;
    return false;
}

vector <Point> water;
vector <pair<int, Point> > pipe;
vector <int> adj[1005];

int w, p, s, x, y, color[1005];

int main(){
    scanf("%d %d", &w, &p);
    for(int i = 0; i < w; i++){
        scanf("%d %d", &x, &y);
        water.push_back(Point(x, y));
    }
    for(int i = 0; i < p; i++){
        scanf("%d %d %d", &s, &x, &y);
        pipe.push_back({s - 1, Point(x, y)});
    }
    for(int i = 0; i < p; i++)
    for(int j = i + 1; j < p; j++){
        if(isOverlap(water[pipe[i].first], pipe[i].second, water[pipe[j].first], pipe[j].second)){
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    bool ans = true;
    for(int i = 0; i < p; i++){
        if(!ans) break;
        if(!color[i]){
            queue <int> q;
            q.push(i);
            color[i] = 1;
            while(!q.empty()){
                int pos = q.front();
                q.pop();
                for(int next : adj[pos]){
                    if(color[next] == color[pos]) ans = false;
                    else if(!color[next]){
                        color[next] = color[pos] == 1 ? 2 : 1;
                        q.push(next);
                    }
                }
            }
        }
    }
    printf("%s", ans ? "possible" : "impossible");
}
