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

void addPoint(long long int x, long long int y){
        P.push_back(Point(x, y));
}

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

int N, x, y;

int main(){
    scanf("%d", &N);
    for(int i = 0;i < N; i++){
        scanf("%d %d", &x, &y);
        addPoint(x, y);
    }
    calcCH();
    printf("%d", CH.size());
}
