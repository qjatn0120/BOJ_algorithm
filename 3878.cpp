#include <bits/stdc++.h>

using namespace std;

struct Point{
    long long int x, y;
    bool operator < (const Point& r) const{
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
    return c > 0 ||(c == 0 && a < b);
}

void getCH(vector <Point> &v){
    P.clear(), CH.clear();
    copy(v.begin(), v.end(), back_inserter(P));
    swap(P[min_element(P.begin(), P.end()) - P.begin()], P[0]);
    sort(P.begin() + 1, P.end(), cmp);
    for(int i = 0; i < P.size(); i++){
        while(CH.size() >= 2 && CCW(CH[CH.size() - 2], CH.back(), P[i]) <= 0) CH.pop_back();
        CH.push_back(P[i]);
    }
    v.clear();
    copy(CH.begin(), CH.end(), back_inserter(v));
}

int T, n, m;
long long int x, y;
vector <Point> v1, v2;

bool sepAble(Point a, Point b){
    bool b1 = true, b2 = true;
    for(Point p : v1) b1 &= (CCW(a, b, p) >= 0);
    for(Point p : v2) b1 &= (CCW(a, b, p) <= 0);
    for(Point p : v1) b2 &= (CCW(a, b, p) <= 0);
    for(Point p : v2) b2 &= (CCW(a, b, p) >= 0);
    return b1 | b2;
}

bool sameLine(vector <Point> &v, Point tar){
    bool ret = false;
    for(int i = 0; i < (int)v.size(); i++){
        Point p1 = v[i], p2 = v[(i + 1) % v.size()];
        if(CCW(p1, p2, tar) == 0){
            ret |= (p1 < tar && tar < p2);
            ret |= (p2 < tar && tar < p1);
        }
    }
    return ret;
}

bool solve(){
    getCH(v1), getCH(v2);
    bool ret = false;
    for(Point p1 : v1)
    for(Point p2 : v2) ret |= sepAble(p1, p2);
    for(Point p : v1) ret &= !sameLine(v2, p);
    for(Point p : v2) ret &= !sameLine(v1, p);
    return ret;
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        v1.clear(), v2.clear();
        while(n--) scanf("%lld %lld", &x, &y), v1.push_back(Point(x, y));
        while(m--) scanf("%lld %lld", &x, &y), v2.push_back(Point(x, y));
        printf("%s\n", solve() ? "YES" : "NO");
    }
}
