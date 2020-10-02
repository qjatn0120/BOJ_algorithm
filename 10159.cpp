#include <bits/stdc++.h>

using namespace std;

const int MX = 105;
const int inf = 987654321;

bool dist[MX][MX];
int N, M, a, b;

int main(){
    for(int i = 0; i < MX * MX; i++) dist[i / MX][i % MX] = false;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        dist[a][b] = true;
    }
    for(int k = 1; k <= N; k++)
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++) dist[i][j] |= dist[i][k] & dist[k][j];
    int cnt;
    for(int i = 1; i <= N; i++){
        cnt = 0;
        for(int j = 1; j <= N; j++){
            if(i == j) continue;
            if(!(dist[i][j] | dist[j][i])) cnt++;
        }
        printf("%d\n", cnt);
    }
}
