#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
const long long int MOD = 1e9 + 7;

long long int node[MX * 4], lazy1[MX * 4], lazy2[MX * 4];

void prop(int n, int nL, int nR){
    node[n] = (node[n] * lazy1[n] + lazy2[n] * (nR - nL + 1)) % MOD;
    if(nL != nR){
        lazy1[n * 2] = (lazy1[n * 2] * lazy1[n]) % MOD;
        lazy1[n * 2 + 1] = (lazy1[n * 2 + 1] * lazy1[n]) % MOD;
        lazy2[n * 2] = (lazy2[n * 2] * lazy1[n] + lazy2[n]) % MOD;
        lazy2[n * 2 + 1] = (lazy2[n * 2 + 1] * lazy1[n] + lazy2[n]) % MOD;
    }
    lazy1[n] = 1, lazy2[n] = 0;
}

long long int diff1 = 1, diff2;

void Update(int n, int L, int R, int nL, int nR){
    if(L == nL && R == nR){
        lazy1[n] = (lazy1[n] * diff1) % MOD;
        lazy2[n] = (lazy2[n] * diff1 + diff2) % MOD;
        prop(n, nL, nR);
        return;
    }
    prop(n, nL, nR);
    int mid = nL + nR >> 1;
    if(R <= mid) Update(n * 2, L, R, nL, mid), prop(n * 2 + 1, mid + 1, nR);
    else if(L > mid) Update(n * 2 + 1, L, R, mid + 1, nR), prop(n * 2, nL, mid);
    else Update(n * 2, L, mid, nL, mid), Update(n * 2 + 1, mid + 1, R, mid + 1, nR);
    node[n] = (node[n * 2] + node[n * 2 + 1]) % MOD;
}

long long int Query(int n, int L, int R, int nL, int nR){
    prop(n, nL, nR);
    if(L == nL && R == nR) return node[n];
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(n * 2, L, R, nL, mid);
    else if(L > mid) return Query(n * 2 + 1, L, R, mid + 1, nR);
    else return (Query(n * 2, L, mid, nL, mid) + Query(n * 2 + 1, mid + 1, R, mid + 1, nR)) % MOD;
}

int N, M, t, x, y, v;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < MX * 4; i++) lazy1[i] = 1;
    for(int i = 1; i <= N; i++){
        scanf("%lld", &diff2);
        Update(1, i, i, 1, N);
    }
    scanf("%d", &M);
    while(M--){
        scanf("%d %d %d", &t, &x, &y);
        if(t == 4) printf("%lld\n", Query(1, x, y, 1, N));
        else{
            scanf("%d", &v);
            if(t == 1) diff1 = 1, diff2 = v;
            else if(t == 2) diff1 = v, diff2 = 0;
            else diff1 = 0, diff2 = v;
            Update(1, x, y, 1, N);
        }
    }
}
