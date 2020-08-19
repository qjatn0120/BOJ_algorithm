#include <bits/stdc++.h>

using namespace std;

const int MX1 = 1e5 + 5, MX2 = 1e3 + 5;
int cache[MX1][MX2];
int myTurn[MX1][MX2];

int DP(int N, int limit){
    if(N == 0) return false;
    if(cache[N][limit] != -1) return cache[N][limit];
    int ret = 0;
    for(int put = 1; put <= limit && put <= N; put++){
        if(DP(N - put, put + 1) == 0){
            ret = true;
            myTurn[N][limit] = put;
            break;
        }
    }
    return cache[N][limit] = ret;
}

int lim = 1, N, tmp;

int main(){
    for(int i = 0; i < MX1; i++)
    for(int j = 0; j < MX2; j++) cache[i][j] = -1;
    scanf("%d", &N);
    if(!DP(N, 1)){printf("NO"); return 0;}
    else printf("YES\n");
    fflush(stdout);
    while(1){
        DP(N, lim);
        int tN = N - myTurn[N][lim], tlim = myTurn[N][lim] + 1;
        printf("%d\n", myTurn[N][lim]);
        fflush(stdout);
        N = tN, lim = tlim;
        if(N == 0) break;
        scanf("%d", &tmp);
        N -= tmp, lim = tmp + 1;
    }
}
