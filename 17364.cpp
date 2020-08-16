#include <bits/stdc++.h>

using namespace std;

int N, K, S, E, t, ans;
vector <pair<int, int> > v;
multiset <int> inTest;
bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
}

int main(){
    scanf("%d %d", &N, &K);
    for(int i = 0; i < N; i++) scanf("%d %d", &S, &E), v.push_back({S, E});
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < N; i++){
        if(v[i].first <= t) continue;
        if(K == 1 || (inTest.size() == K - 1 && (*inTest.begin()) >= v[i].first)){
            ans++;
            t = v[i].second;
            inTest.clear();
        }else{
            auto it = inTest.lower_bound(v[i].first);
            if(it != inTest.begin()) it--, inTest.erase(it);
            inTest.insert(v[i].second);
        }
    }
    printf("%d", ans);
}