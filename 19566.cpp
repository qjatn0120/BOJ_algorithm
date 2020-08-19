#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

map <long long int, int> mp;
int N, K;
long long int ans, A[MX];

int main(){
    scanf("%d %d", &N, &K);
    for(int i = 1; i <= N; i++) scanf("%lld", &A[i]), A[i] -= K;
    for(int i = 2; i <= N; i++) A[i] += A[i - 1];
    for(int i = 0; i <= N; i++){
        if(mp.find(A[i]) != mp.end()) ans += mp[A[i]];
        auto ret = mp.insert({A[i], 1});
        if(!ret.second) ret.first->second++;
    }
    printf("%lld", ans);
}
