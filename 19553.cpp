#include <bits/stdc++.h>

using namespace std;

int cache[1005][1005][105];
int N, a[1005], sum[1005];

int getSum(int L, int R){
    if(L == N + 1) L = 1;
    if(R == 0) R = N;
    if(L <= R) return sum[R] - sum[L - 1];
    return getSum(1, R) + getSum(L, N);
}

int DP(int L, int R, int t){
    if(L == N + 1) L = 1;
    if(R == 0) R = N;
    if(L == R) return a[L];
    if(cache[L][R][t]) return cache[L][R][t];
    int ret = 0;
    if(t - a[L] >= 0) ret = DP(L + 1, R, t - a[L]) + a[L];
    else ret = getSum(L + 1, R) - DP(L + 1, R, a[L] - t - 1) + a[L];
    if(t - a[R] >= 0) ret = max(ret, DP(L, R - 1, t - a[R]) + a[R]);
    else ret = max(ret, getSum(L, R - 1) - DP(L, R - 1, a[R] - t - 1) + a[R]);
    return cache[L][R][t] = ret;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
    int ans = 0;
    for(int i = 1; i <= N; i++) ans = max(ans, DP(i, i - 1, 0));
    printf("%d", ans);
}
