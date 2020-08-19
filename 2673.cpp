#include <bits/stdc++.h>

using namespace std;

int N, c[105][105], DP[105][105], a, b;

int main(){
    scanf("%d", &N);
    while(N--){
        scanf("%d %d", &a, &b);
        if(a > b) swap(a, b);
        c[a][b] = 1;
    }
    for(int j = 2; j <= 100; j++)
    for(int i = 1; i < j; i++)
    for(int k = i; k <= j; k++) DP[i][j] = max(DP[i][j], DP[i][k] + DP[k + 1][j - 1] + c[k][j]);
    printf("%d", DP[1][100]);
}
