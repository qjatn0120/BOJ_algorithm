#include <bits/stdc++.h>

using namespace std;

const int MX = 4e5 + 5;
const long long int MOD = 1e9 + 7;

long long int node[MX * 3];

void update(int n, int nL, int nR, int tar){
    if(tar < nL || tar > nR) return;
    node[n]++;
    if(nL == nR) return;
    int mid = nL + nR >> 1;
    update(n * 2, nL, mid, tar);
    update(n * 2 + 1, mid + 1, nR, tar);
}

long long int query(int n, int nL, int nR, int L, int R){
    if(L > nR || R < nL) return 0;
    if(L <= nL && nR <= R) return node[n];
    int mid = nL + nR >> 1;
    return query(n * 2, nL, mid, L, R) + query(n * 2 + 1, mid + 1, nR, L, R);
}

vector <int> row[MX];
int N, X, Y;
long long int ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d", &X, &Y);
        X += 2e5, Y += 2e5;
        row[Y].push_back(X);
    }
    for(int i = MX - 1; i >= 0; i--){
        for(int j = 0; j < (int)row[i].size(); j++) ans += query(1, 0, MX - 1, 0, row[i][j] - 1) * query(1, 0, MX - 1, row[i][j] + 1, MX - 1), ans %= MOD;
        for(int j = 0; j < (int)row[i].size(); j++) update(1, 0, MX - 1, row[i][j]);
    }
    printf("%lld", ans);
}
