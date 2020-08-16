#include <bits/stdc++.h>

using namespace std;

struct Point{
    long long int x, y;
    bool operator < (const Point &r) const{
        if(x == r.x) return y < r.y;
        return x < r.x;
    }
    Point(long long int x, long long int y) : x(x), y(y) {}
};

vector <Point> P, CH;

long long int CCW(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b){
    long long int c = CCW(P[0], a, b);
    return (c > 0) || (c == 0 && a < b);
}

void calcCH(){
    int st = 0;
    for(int i = 0; i < P.size(); i++){
        if(P[i] < P[st]) st = i;
    }
    swap(P[0], P[st]);
    sort(P.begin() + 1, P.end(), cmp);
    for(int i = 0; i < P.size(); i++){
        while(CH.size() >= 2 && CCW(CH[CH.size() - 2], CH.back(), P[i]) <= 0) CH.pop_back();
        CH.push_back(P[i]);
    }
}

double dist(Point a, Point b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point gap(int a){
    int next = (a + 1) % CH.size();
    return Point(CH[next].x - CH[a].x, CH[next].y - CH[a].y);
}

int C, x, y;

int main(){
    scanf("%d", &C);
    for(int i = 0; i < C; i++){
        scanf("%d %d", &x, &y);
        P.push_back(Point(x, y));
    }
    calcCH();
    int p1 = min_element(CH.begin(), CH.end()) - CH.begin();
    int p2 = max_element(CH.begin(), CH.end()) - CH.begin();
    double ans = dist(CH[p1], CH[p2]);
    for(int i = 0; i < C * 2; i++){
        if(CCW(gap(p1), Point(0, 0), gap(p2)) > 0) p1 = (p1 + 1) % CH.size();
        else p2 = (p2 + 1) % CH.size();
        ans = max(ans, dist(CH[p1], CH[p2]));
    }
    printf("%.10lf", ans);
}
