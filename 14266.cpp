#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
const double err = 1e-12;

struct Dot{
    double deg;
    bool add;
    Dot(double d, bool b) : deg(d), add(b) {}
};

bool cmp(Dot p1, Dot p2){
    if(abs(p1.deg - p2.deg) < err) return p1.add > p2.add;
    return p1.deg < p2.deg;
}

vector <Dot> dot;

int n, cnt, ans;
int X1, Y1, X2, Y2;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        double deg1 = atan2((double)Y1, (double)X1);
        double deg2 = atan2((double)Y2, (double)X2);
        if(deg1 > deg2) swap(deg1, deg2);
        dot.push_back({deg1, true});
        dot.push_back({deg2, false});
    }
    sort(dot.begin(), dot.end(), cmp);
    for(int i = 0; i < dot.size(); i++){
        if(dot[i].add) cnt++;
        else cnt--;
        ans = max(cnt, ans);
    }
    printf("%d", ans);
}
