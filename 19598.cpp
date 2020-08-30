#include <bits/stdc++.h>

using namespace std;

int N, s, e, ans, cnt;

vector <pair<int, int> > v;

int main(){
    scanf("%d", &N);
    while(N--){
        scanf("%d %d", &s, &e);
        v.push_back({s, 1});
        v.push_back({e, -1});
    }
    sort(v.begin(), v.end());
    for(auto i : v){
        cnt += i.second;
        ans = max(ans, cnt);
    }
    printf("%d", ans);
}
