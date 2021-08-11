#include <bits/stdc++.h>

using namespace std;

int T, N;
vector <pair<int, int> > p;

pair <int, int> operator + (pair<int, int> p1, pair<int, int> p2){
    return {p1.first + p2.first, p1.second + p2.second};
}

pair <int, int> operator - (pair<int, int> p1, pair<int, int> p2){
    return {p1.first - p2.first, p1.second - p2.second};
}

double calc(pair <int, int> p1, pair <int, int> p2, int n1, int n2);

int main(){
    scanf("%d", &T);
    while(T--){
        p.clear();
        scanf("%d", &N);
        int tmp1, tmp2;
        for(int i = 0; i < N; i++) scanf("%d %d", &tmp1, &tmp2), p.push_back({tmp1, tmp2});
        printf("%.10lf\n", calc({0, 0}, {0, 0}, 0, 0));
    }
}

double calc(pair <int, int> p1, pair <int, int> p2, int n1, int n2){
    if(n1 + n2 == N){
        pair <int, int> dist = p1 - p2;
        return sqrt((double)dist.first * dist.first + (double)dist.second * dist.second);
    }
    if(n1 == N / 2) return calc(p1, p2 + p[n1 + n2], n1, n2 + 1);
    else if(n2 == N / 2) return calc(p1 + p[n1 + n2], p2, n1 + 1, n2);
    double re1 = calc(p1 + p[n1 + n2], p2, n1 + 1, n2);
    double re2 = calc(p1, p2 + p[n1 + n2], n1, n2 + 1);
    return min(re1, re2);
}
