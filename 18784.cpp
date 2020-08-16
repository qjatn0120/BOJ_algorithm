#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
const long long int MOD = 1e9 + 7;

bool cmp(pair<int, int> p1, pair<int, int> p2){
    if(p1.second == p2.second) return p1.first < p2.first;
    return p1.second > p2.second;
}

long long int solve();

vector <pair<int, int> > pos;
long long int Ysum[MX], Ycnt[MX];

int N, X, Y;
long long int ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d", &X, &Y);
        pos.push_back({X + (int)1e4, Y + (int)1e4});
    }
    sort(pos.begin(), pos.end(), cmp);
    ans = solve();
    for(int i = 0; i < pos.size(); i++) pos[i].first = (int)2e4 - pos[i].first;
    sort(pos.begin(), pos.end(), cmp);
    ans = (ans + solve()) % MOD;
    for(int i = 0; i < pos.size(); i++) pos[i].second = (int)2e4 - pos[i].second;
    sort(pos.begin(), pos.end(), cmp);
    ans = (ans + solve()) % MOD;
    for(int i = 0; i < pos.size(); i++) pos[i].first = (int)2e4 - pos[i].first;
    sort(pos.begin(), pos.end(), cmp);
    ans = (ans + solve()) % MOD;
    printf("%lld", ans);
}

long long int solve(){
    long long int sum = 0, cnt = 0, ret = 0;
    for(int i = 0; i < MX; i++) Ysum[i] = Ycnt[i] = 0;
    for(int i = 0; i < (int)pos.size(); i++){
        if(i && pos[i - 1].second != pos[i].second) sum = cnt= 0;
        ret = (ret + ((Ysum[pos[i].first] - pos[i].second * Ycnt[pos[i].first]) % MOD) * ((cnt * pos[i].first - sum) % MOD)) % MOD;
        ret = (ret + MOD) % MOD;
        Ysum[pos[i].first] = (Ysum[pos[i].first] + pos[i].second) % MOD;
        Ycnt[pos[i].first]++;
        sum = (sum + pos[i].first) % MOD;
        cnt++;
    }
    return ret;
}
