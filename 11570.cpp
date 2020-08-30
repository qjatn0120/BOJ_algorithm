#include <bits/stdc++.h>

using namespace std;

const int MX = 2005;

int N, a[MX], cache[MX][MX];
int DP(int p, int q){
    if(p < q) swap(p, q);
    if(cache[p][q] != -1) return cache[p][q];
    int ret = INT_MAX;
    if(p == q + 1){
        for(int k = 0; k < q; k++) ret = min(ret, DP(k, q) + (k ? abs(a[p] - a[k]) : 0));
    }else ret = DP(p - 1, q) + abs(a[p] - a[p - 1]);
    return cache[p][q] = ret;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &a[i]);
    for(int i = 0; i <= 2000; i++)
    for(int j = 0; j <= 2000; j++) cache[i][j] = -1;
    cache[0][0] = cache[1][0] = 0;
    int ans = INT_MAX;
    for(int i = 0; i < N; i++) ans = min(ans, DP(N, i));
    printf("%d", ans);
}
