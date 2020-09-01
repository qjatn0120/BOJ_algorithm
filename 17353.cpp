#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

int N, Q, A[MX], t, x, l, r;
long long int node[MX * 4], lazy[MX * 4];

void prop(int n, int nL, int nR){
    if(!lazy[n]) return;
    node[n] += lazy[n] * (nR - nL + 1);
    if(nL != nR){
        lazy[n * 2] += lazy[n];
        lazy[n * 2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void makeTree(int n, int nL, int nR){
    if(nL == nR){
        node[n] = A[nL];
        return;
    }
    int mid = nL + nR >> 1;
    makeTree(n * 2, nL, mid);
    makeTree(n * 2 + 1, mid + 1, nR);
    node[n] = node[n * 2] + node[n * 2 + 1];
}

void Update(int n, int L, int R, int nL, int nR, int diff){
    if(L == nL && R == nR){
        lazy[n] += diff;
        prop(n, nL, nR);
        return;
    }
    int mid = nL + nR >> 1;
    prop(n, nL, nR);
    if(R <= mid) Update(n * 2, L, R, nL, mid, diff), prop(n * 2 + 1, mid + 1, nR);
    else if(L > mid) Update(n * 2 + 1, L, R, mid + 1, nR, diff), prop(n * 2, nL, mid);
    else Update(n * 2, L, mid, nL, mid, diff), Update(n * 2 + 1, mid + 1, R, mid + 1, nR, diff);
    node[n] = node[n * 2] + node[n * 2 + 1];
}

long long int Query(int n, int L, int R, int nL, int nR){
    prop(n, nL, nR);
    if(L == nL && R == nR) return node[n];
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(n * 2, L, R, nL, mid);
    else if(L > mid) return Query(n * 2 + 1, L, R, mid + 1, nR);
    else return Query(n * 2, L, mid, nL, mid) + Query(n * 2 + 1, mid + 1, R, mid + 1, nR);
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &A[i]);
    for(int i = N; i; i--) A[i] -= A[i - 1];
    makeTree(1, 1, N);
    scanf("%d", &Q);
    for(int i = 0; i < Q; i++){
        scanf("%d", &t);
        if(t == 1){
            scanf("%d %d", &l, &r);
            Update(1, l, r, 1, N, 1);
            if(r != N) Update(1, r + 1, r + 1, 1, N, -(r - l + 1));
        }else{
            scanf("%d", &x);
            printf("%lld\n", Query(1, 1, x, 1, N));
        }
    }
}
