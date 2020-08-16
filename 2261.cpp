#include <bits/stdc++.h>

using namespace std;

vector <pair<long long int, long long int> > dots;
int n, x, y;

bool cmp(pair<long long int, long long int> p1, pair<long long int, long long int> p2){return p1.second < p2.second;}
long long int dist(pair<long long int, long long int> p1, pair<long long int, long long int> p2){
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}
long long int minDist(int L, int R);

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &x, &y);
        dots.push_back({x, y});
    }
    sort(dots.begin(), dots.end());
    printf("%lld", minDist(0, (int)dots.size() - 1));
}

long long int minDist(int L, int R){
    long long int ret = LONG_LONG_MAX;
    if(L == R) return ret;
    int m = L + R >> 1;
    ret = min(ret, minDist(L, m));
    ret = min(ret, minDist(m + 1, R));
    vector <pair<long long int, long long int> > mid;
    int split = dots[m].first;
    for(int i = L; i <= R; i++){
        long long int gap = split - dots[i].first;
        if(gap * gap < ret) mid.push_back(dots[i]);
    }
    sort(mid.begin(), mid.end(), cmp);
    for(int i = 0; i < (int)mid.size(); i++){
        for(int j = i + 1; j < (int)mid.size() && (mid[i].second - mid[j].second) * (mid[i].second - mid[j].second) < ret; j++){
            ret = min(ret, dist(mid[i], mid[j]));
        }
    }
    return ret;
}
