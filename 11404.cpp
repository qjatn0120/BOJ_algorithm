#include <bits/stdc++.h>

using namespace std;

const int MX = 105;
const int inf = 987654321;

int N, M, a, b, c, dist[MX][MX];

int main(){
    for(int i = 0; i < MX * MX; i++) dist[i / MX][i % MX] = inf;
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) dist[i][i] = 0;
    for(int i = 0; i < M; i++){
        scanf("%d %d %d", &a, &b, &c);
        dist[a][b] = min(dist[a][b], c);
    }
    for(int k = 1; k <= N; k++)
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++) dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++) printf("%d ", dist[i][j] == inf ? 0 : dist[i][j]);
        printf("\n");
    }
}
