#include <bits/stdc++.h>

using namespace std;

int n, W[16][16], m[70000][20];//m[도시 방문 정보][현재 위치]
int ans = 1987654321;

int DP(int visit, int pos);

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) scanf("%d", &W[i][j]);
    ans = DP((1 << n) - 1, 0);
    printf("%d", ans);
}

int DP(int visit, int pos){
    if(m[visit][pos]) return m[visit][pos];
    if(!visit) return 0;
    if(visit == 1)
        if(W[0][pos]) return W[0][pos];
        else return 1987654321;
    int mn = 1987654321;
    for(int i = 1; i < n; i++)
        if((visit & (1 << i)) && W[i][pos]) mn = min(mn, DP(visit - (1 << i), i) + W[i][pos]);
    return m[visit][pos] = mn;
}
