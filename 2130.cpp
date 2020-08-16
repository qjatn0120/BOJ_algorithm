#include <bits/stdc++.h>

using namespace std;

int N, b, h, w, d;
long long int V;

vector <pair<int, long long int> > v;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d %d %d", &b, &h, &w, &d);
        v.push_back({b, w * d});
        v.push_back({b + h, -w * d});
    }
    scanf("%lld", &V);
    sort(v.begin(), v.end());
    long long int Area = 0;
    int pos = 0;
    bool able = true;
    for(int  i = 0; i < (int)v.size() - 1; i++){
        Area += v[i].second;
        pos = v[i].first;
        if(Area * (v[i + 1].first - pos) >= V) break;
        V -= Area * (v[i + 1].first - pos);
        if(i == (int)v.size() - 2 && V) able = false;
    }
    if(!able) printf("OVERFLOW");
    else{
        double ans = pos;
        ans += (double)V / Area;
        printf("%.2lf", ans);
    }
}
