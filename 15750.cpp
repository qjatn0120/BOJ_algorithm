#include <bits/stdc++.h>

using namespace std;

int N, a, b;
vector <pair<int, int> > v;

long long int solve();

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d", &a, &b);
        v.push_back({a, b});
    }
    long long int ans = solve();
    for(int i = 0; i < N; i++) v[i].first *= -1, v[i].second *= -1;
    ans = min(ans, solve());
    printf("%lld", ans);
}

long long int solve(){
    long long int ret, dist = 0, sum = 0;
    vector <pair<int, int> > seg;
    for(int i = 0; i < N; i++){
        dist += abs(v[i].first - v[i].second);
        if(v[i].first > v[i].second) continue;
        else if(v[i].first <= 0 && v[i].second > 0){
            seg.push_back({0, -1});
            seg.push_back({v[i].second, 2});
            seg.push_back({v[i].second * 2, -1});
        }else if(v[i].first > 0 && v[i].first * 2 < v[i].second){
            seg.push_back({v[i].first * 2, -1});
            seg.push_back({v[i].second, 2});
            seg.push_back({2 * (v[i].second - v[i].first), -1});
        }
    }
    ret = dist;
    int befX = 0;
    sort(seg.begin(), seg.end());
    for(int i = 0; i < seg.size(); i++){
        dist += sum * (seg[i].first - befX);
        ret = min(ret, dist);
        befX = seg[i].first;
        sum += seg[i].second;
    }
    return ret;
}
