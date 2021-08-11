#include <bits/stdc++.h>

using namespace std;

int T, N, M, cache[35][35];
int DP(int a, int b);

int main(){
    scanf("%d", &T);
    for(int rep = 0; rep < T; rep++){
        scanf("%d %d", &N, &M);
        if(N > M) swap(N, M);
        printf("%d\n", DP(N, M));
    }
}

int DP(int a, int b){
    if(cache[a][b]) return cache[a][b];
    if(a == 0 || a == b) return 1;
    return cache[a][b] = DP(a - 1, b - 1) + DP(a, b - 1);
}
