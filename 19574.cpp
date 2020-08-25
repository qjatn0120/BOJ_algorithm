#include <bits/stdc++.h>

using namespace std;

struct Circle{
    double R, x, y;
    Circle(double R, double x, double y) : R(R), x(x), y(y) {}
};

const double PI = acos(-1);
int N;
vector <Circle> v;
double px, py, r, x, y;

double CCW(pair<double, double> p1, pair <double, double> p2){
    return p1.first * p2.second - p1.second * p2.first;
}

double getDiff(Circle &C, double dir){
    bool Plus = CCW({cos(dir), sin(dir)}, {C.x - px, C.y - py}) > 0;
    double a = tan(dir), b = -1, c = -px * tan(dir) + py;
    double dist = abs(a * C.x + b * C.y + c) / sqrt(a * a + b * b);
    double ret;
    if(dist >= C.R) ret = PI * C.R * C.R;
    else{
        double theta = acos(dist / C.R);
        theta *= 2;
        ret = 0.5 * C.R * C.R * theta - 0.5 * C.R * C.R * sin(theta);
        ret = PI * C.R * C.R - 2 * ret;
    }
    return Plus ? ret : -ret;
}

double diffSum(double dir){
    double diff = getDiff(v[0], dir);
    for(int i = 1; i <= N; i++) diff -= getDiff(v[i], dir);
    return diff;
}

int main(){
    scanf("%lf %lf %lf", &r, &px, &py);
    v.push_back(Circle(r, 0, 0));
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%lf %lf %lf", &x, &y, &r);
        v.push_back(Circle(r, x, y));
    }
    double lo = - PI / 2, hi = PI / 2;
    if(diffSum(lo) > diffSum(hi)) swap(lo, hi);
    while(abs(hi - lo) > 1e-15){
        double mid = (lo + hi) / 2;
        if((diffSum(mid) > 0)) hi = mid;
        else lo = mid;
    }
    printf("%.15lf", lo);
}