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

vector <Point> P;

long long int CCW(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b){
    long long int c = CCW(P[0], a, b);
    return c > 0 || (c == 0 && a < b);
}

int n, x, y;
char c;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d %c", &x, &y, &c);
        if(c == 'Y') P.push_back(Point(x, y));
    }
    int st = 0;
    for(int i = 0; i < P.size(); i++){
        if(P[i] < P[st]) st = i;
    }
    swap(P[0], P[st]);
    sort(P.begin() + 1, P.end(), cmp);
    int p = P.size() - 2;
    while(CCW(P.front(), P.back(), P[p]) == 0) p--;
    p++;
    reverse(P.begin() + p, P.end());
    printf("%d\n", P.size());
    for(int i = 0; i < P.size(); i++) printf("%lld %lld\n", P[i].x, P[i].y);
}
