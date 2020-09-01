#include <bits/stdc++.h>

using namespace std;

const long long int MOD = 1e9 + 7;

int N, t, group[505], cnt[505], cnt2[505];
long long int fac[505];
vector <bool> v[505];

int diff(vector <bool> &v1, vector <bool> &v2){
    int ret = 0;
    for(int i = 0; i < v1.size(); i++) ret += (v1[i] != v2[i]);
    return ret;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++){
        scanf("%d", &t);
        v[i].push_back(t);
        cnt2[i] += t;
    }
    cnt[0] = 1;
    for(int j = 1; j < N; j++){
        group[j] = j;
        for(int i = 0; i < j; i++){
            if(diff(v[i], v[j]) == 0){
                group[j] = i;
                break;
            }
        }
        cnt[group[j]]++;
    }
    fac[0] = 1;
    for(int i = 1; i < 505; i++) fac[i] = (fac[i - 1] * i) % MOD;
    long long int ans = 1;
    for(int i = 0; i < N; i++) ans = (ans * fac[max(0, cnt[i] - 1)]) % MOD;
    for(int j = 0; j < N; j++){
        if(group[j] != j || cnt[j] > 1) continue;
        for(int i = 0; i < N; i++){
            if(i == j) continue;
            if(group[i] != i) continue;
            if(diff(v[i], v[j]) == 1 && cnt2[i] < cnt2[j]) ans = (ans * cnt[i]) % MOD;
        }
    }
    printf("%lld", ans);
}
