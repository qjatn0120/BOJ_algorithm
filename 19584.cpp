#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

map <int, long long int> mp;
int N, M, x, y[MX], u, v, c;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> x >> y[i];
    for(int i = 1; i <= M; i++){
        cin >> u >> v >> c;
        if(y[u] > y[v]) swap(u, v);
        auto ret = mp.insert({y[u], c});
        if(!ret.second) ret.first->second += c;
        ret = mp.insert({y[v] + 1, -c});
        if(!ret.second) ret.first->second -= c;
    }
    long long int ans = 0, sum = 0;
    for(auto i : mp) sum += i.second, ans = max(ans, sum);
    cout << ans;
}
