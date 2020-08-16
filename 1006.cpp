#include <bits/stdc++.h>

using namespace std;

const int MX = 10005;

int T, N, W;
int num[MX][2];
int cache[MX][4];

void ClearCache();
int DP1(int a, int b);
int DP2(int a, int b);

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &W);
        for(int i = 1; i <= N; i++) scanf("%d", &num[i][0]);
        for(int i = 1; i <= N; i++) scanf("%d", &num[i][1]);
        ClearCache();
        int ans = DP1(N, 0);
        if(num[1][0] + num[N][0] <= W){
            ClearCache();
            ans = min(ans, DP2(N, 2) + 1);
        }
        if(num[1][1] + num[N][1] <= W){
            for(int i = 1; i <= N; i++) swap(num[i][0], num[i][1]);
            ClearCache();
            ans = min(ans, DP2(N, 2) + 1);
        }
        if(num[1][0] + num[N][0] <= W && num[1][1] + num[N][1] <= W){
            ClearCache();
            for(int i = 1; i <= N - 1; i++) num[i][0] = num[i + 1][0], num[i][1] = num[i + 1][1];
            ans = min(ans, DP1(N - 2, 0) + 2);
        }
        printf("%d\n", ans);
    }
}

void ClearCache(){
    for(int i = 0; i < MX; i++)
        for(int j = 0; j < 4; j++) cache[i][j] = -1;
}

int DP1(int a, int b){
    if(cache[a][b] != -1) return cache[a][b];
    if(a == 0 && b == 0) return 0;
    if(b == 0){
        int re = min(DP1(a, 1), DP1(a, 2)) + 1;
        if(num[a][0] + num[a][1] <= W) re = min(re, DP1(a - 1, 0) + 1);
        if(a > 1 && num[a][0] + num[a - 1][0] <= W) re = min(re, DP1(a, 3) + 1);
        return cache[a][b] = re;
    }
    if(b == 1){
        if(a > 1 && num[a][0] + num[a - 1][0] <= W){
            return cache[a][b] = min(DP1(a - 1, 0), DP1(a - 1, 2)) + 1;
        }
        return cache[a][b] = DP1(a - 1, 0) + 1;
    }
    if(b == 2){
        if(a > 1 && num[a][1] + num[a - 1][1] <= W){
            return cache[a][b] = min(DP1(a - 1, 0), DP1(a - 1, 1)) + 1;
        }
        return cache[a][b] = DP1(a - 1, 0) + 1;
    }
    if(b == 3){
        int re = DP1(a - 1, 2) + 1;
        if(a > 1 && num[a][1] + num[a - 1][1] <= W) re = min(re, DP1(a - 2, 0) + 1);
        return cache[a][b] = re;
    }
}

int DP2(int a, int b){
    if(cache[a][b] != -1) return cache[a][b];
    if(a == 0 && b == 0) return cache[a][b] = 0;
    if(a == 1 && b == 1) return cache[a][b] = 0;
    if(b == 0){
        int re = min(DP2(a, 1), DP2(a, 2)) + 1;
        if(num[a][0] + num[a][1] <= W) re = min(re, DP2(a - 1, 0) + 1);
        if(a > 1 && num[a][0] + num[a - 1][0] <= W) re = min(re, DP2(a, 3) + 1);
        return cache[a][b] = re;
    }
    if(b == 1){
        if(a > 1 && num[a][0] + num[a - 1][0] <= W){
            return cache[a][b] = min(DP2(a - 1, 0), DP2(a - 1, 2)) + 1;
        }
        return cache[a][b] = DP2(a - 1, 0) + 1;
    }
    if(b == 2){
        if(a > 1 && num[a][1] + num[a - 1][1] <= W){
            return cache[a][b] = min(DP2(a - 1, 0), DP2(a - 1, 1)) + 1;
        }
        return cache[a][b] = DP2(a - 1, 0) + 1;
    }
    if(b == 3){
        int re = DP2(a - 1, 2) + 1;
        if(a > 1 && num[a][1] + num[a - 1][1] <= W) re = min(re, DP2(a - 2, 0) + 1);
        return cache[a][b] = re;
    }
}
