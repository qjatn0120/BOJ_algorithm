#include <bits/stdc++.h>

using namespace std;

const int MOD = 9901, MX = 14;
int N, M;
int cache[MX * MX][1 << MX];

int DP(int p, int bit){
    if(bit & 1) return cache[p][bit] = DP(p - 1, bit >> 1);
    if(p <= 0) return p != 0;
    if(cache[p][bit] != -1) return cache[p][bit];
    int ret = 0;
    if((bit & 2) == 0 && (p % M) != 0) ret += DP(p - 2, bit >> 2);
    if(p >= M) ret += DP(p - 1, (bit >> 1) + (1 << M - 1));
    ret %= MOD;
    return cache[p][bit] = ret;
}

int main(){
    for(int i = 0; i < MX * MX; i++)
    for(int j = 0; j < (1 << MX); j++) cache[i][j] = -1;
    scanf("%d %d", &N, &M);
    printf("%d", DP(N * M - 1, 0));
}
