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
vector <Point> v1, v2;

long long int CCW(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y)  - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b){
    long long int c = CCW(P[0], a, b);
    return c > 0 || (c == 0 && a < b);
}

void calcCH(){
    CH.clear();
    int st = 0;
    for(int i = 0; i < P.size(); i++){
        if(P[i] < P[st]) st = i;
    }
    swap(P[st], P[0]);
    sort(P.begin() + 1, P.end(), cmp);
    for(int i = 0; i < P.size(); i++){
        while(CH.size() >= 2 && CCW(CH[CH.size() - 2], CH.back(), P[i]) <= 0) CH.pop_back();
        CH.push_back(P[i]);
    }
}

bool sepAble(Point a, Point b){
    bool able1 = true, able2 = true;
    for(int i = 0; i < v1.size(); i++){
        if(CCW(a, b, v1[i]) < 0) able1 = false;
    }
    for(int i = 0; i < v2.size(); i++){
        if(CCW(a, b, v2[i]) > 0) able1 = false;
    }
    for(int i = 0; i < v1.size(); i++){
        if(CCW(a, b, v1[i]) > 0) able2 = false;
    }
    for(int i = 0; i < v2.size(); i++){
        if(CCW(a, b, v2[i]) < 0) able2 = false;
    }
    return able1 || able2;
}

void Copy(vector <Point> &from, vector <Point> &to){
    to.clear();
    for(int i = 0; i < from.size(); i++) to.push_back(from[i]);
}

int T, n, m, x, y;

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &n, &m);
        v1.clear(), v2.clear();
        for(int i = 0; i < n; i++){
            scanf("%d %d", &x, &y);
            v1.push_back(Point(x, y));
        }
        for(int i = 0; i < m; i++){
            scanf("%d %d", &x, &y);
            v2.push_back(Point(x, y));
        }
        Copy(v1, P);
        calcCH();
        Copy(CH, v1);
        Copy(v2, P);
        calcCH();
        Copy(CH, v2);
        bool able = false;
        for(int i = 0; i < v1.size(); i++)
        for(int j = 0; j < v2.size(); j++){
            if(sepAble(v1[i], v2[j])) able = true;
        }
        for(int i = 0; i < v1.size(); i++)
        for(int j = 0; j < v2.size(); j++){
            Point p1 = v1[i], p2 = v1[(i + 1) % v1.size()];
            Point tar = v2[j];
            if(CCW(p1, p2, tar) == 0){
                if(p1 < tar && tar < p2) able = false;
                if(p2 < tar && tar < p1) able = false;
            }
        }
        v1.swap(v2);
        for(int i = 0; i < v1.size(); i++)
        for(int j = 0; j < v2.size(); j++){
            Point p1 = v1[i], p2 = v1[(i + 1) % v1.size()];
            Point tar = v2[j];
            if(CCW(p1, p2, tar) == 0){
                if(p1 < tar && tar < p2) able = false;
                if(p2 < tar && tar < p1) able = false;
            }
        }
        printf("%s\n", able ? "YES" : "NO");
    }
}
