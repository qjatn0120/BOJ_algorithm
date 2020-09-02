#include <bits/stdc++.h>

using namespace std;

const int MX = 3005;

long long int inf = LONG_LONG_MAX / 10;
long long int N, M, L, a[MX], b[MX], cache[MX][MX][2];

long long int dist(int n, int m){
    return (a[n] - b[m]) * (a[n] - b[m]) + L * L;
}

long long int DP(int n, int m, int next){
    if(n == 0 || m == 0) return inf;
    if(cache[n][m][next]) return cache[n][m][next];
    long long int ret1 = DP(n - 1, m, 0) + dist(n, m) * (next == 0 ? N + M - 1 : (n + m - 1) * (N + M - n - m + 1));
    long long int ret2 = DP(n, m - 1, 1) + dist(n, m) * (next == 1 ? N + M - 1 : (n + m - 1) * (N + M - n - m + 1));
    return cache[n][m][next] = min(ret1, ret2);
}

int main(){
    scanf("%lld %lld %lld", &N, &M, &L);
    for(int i = 1; i <= N; i++) scanf("%lld", &a[i]);
    for(int i = 1; i <= M; i++) scanf("%lld", &b[i]);
    cache[1][1][0] = cache[1][1][1] = dist(1, 1) * (N + M - 1);
    printf("%lld", DP(N, M, 0));
}
