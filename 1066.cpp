#include <bits/stdc++.h>

using namespace std;

long long int MOD = 1e9 + 7;
long long int cache[1005][10][11][10];
int N, A;

long long int DP(int n, int a, int bef, int now){
    if(bef != 10 && bef > now) return 0;
    if(a > A) return 0;
    if(n == N) return a == A;
    if(cache[n][a][bef][now] != -1) return cache[n][a][bef][now];
    long long int ret = 0;
    for(int next = now; next < 10; next++){
        if(bef == 10 || next - now == now - bef) ret = (ret + DP(n + 1, a, now, next)) % MOD;
        else ret = (ret + DP(n + 1, a + 1, 10, next));
    }
    return cache[n][a][bef][now] = ret;
}

int main(){
    for(int i = 0; i < 1005; i++)
    for(int j = 0; j < 10; j++)
    for(int k = 0; k < 11; k++)
    for(int l = 0; l < 10; l++) cache[i][j][k][l] = -1;
    scanf("%d %d", &N, &A);
    if(N == 1){
        if(A == 1) printf("9");
        else printf("0");
        return 0;
    }
    long long int ans = 0;
    for(int i = 11; i < 100; i++) ans += DP(2, 1, i / 10, i % 10);
    printf("%lld", ans % MOD);
    return 0;
}
