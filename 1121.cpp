#include <bits/stdc++.h>

using namespace std;

long long int cache[55][15];
long long int DP[10][50005], ans;
int arr[55], N, K;

long long int C(int n, int r){
    if(cache[n][r]) return cache[n][r];
    if(n == r || r == 0) return  cache[n][r] = 1;
    return cache[n][r] = C(n - 1, r) + C(n - 1, r - 1);
}

void update(int idx){
    for(int num = 9; num; num--){
        for(int len = 50000; len - arr[idx] >= 0; len--) DP[num][len] += DP[num - 1][len - arr[idx]];
    }
}

int main(){
    DP[0][0] = 1;
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &arr[i]);
    scanf("%d", &K);
    if(N < K || K < 3){printf("0"); return 0;}
    sort(arr, arr + N);
    ans = C(N, K);
    for(int i = 0; i < N; i++){
        if(i >= K - 1) for(int j = 0; j <= arr[i]; j++) ans -= DP[K - 1][j];
        update(i);
    }
    printf("%lld", ans);
}
