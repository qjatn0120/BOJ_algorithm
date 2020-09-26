#include <bits/stdc++.h>

int N, M, arr[105], ans;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; i++) scanf("%d", &arr[i]);
    for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++)
    for(int k = 0; k < N; k++){
        if(i == j || j == k || k == i) continue;
        int sum = arr[i] + arr[j] + arr[k];
        if(sum <= M && ans < sum) ans = sum;
    }
    printf("%d", ans);
}
