#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

//root => 1번
//부모 노드 n => 자식 노드는 2 * n, 2 * n + 1

long long int node[MX * 4], A, B, C;
int N, M, K;

void Update(int n, int L, int R, int b, long long int c);//b번째 수를 c로 변경
long long int Query(int n, int L, int R, int b, int c);//A[b ~ c] 출력

int main(){
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1; i <= N; i++){
        scanf("%lld", &A);
        Update(1, 1, N, i, A);
    }
    for(int i = 1; i <= M + K; i++){
        scanf("%lld %lld %lld", &A, &B, &C);
        if(A == 1) Update(1, 1, N, B, C);
        else printf("%lld\n", Query(1, 1, N, B, C));
    }
}

void Update(int n, int L, int R, int b, long long int c){
    if(L == R){
        node[n] = c;
        return;
    }
    int mid = L + R >> 1;
    if(b <= mid) Update(n * 2, L, mid, b, c);
    else Update(n * 2 + 1, mid + 1, R, b, c);
    node[n] = node[n * 2] + node[n * 2 + 1];
}

long long int Query(int n, int L, int R, int b, int c){
    if(L == b && R == c) return node[n];
    int mid = L + R >> 1;
    if(c <= mid) return Query(n * 2, L, mid, b, c);
    if(b > mid) return Query(n * 2 + 1, mid + 1, R, b, c);
    return Query(n * 2, L, mid, b, mid) + Query(n * 2 + 1, mid + 1, R, mid + 1, c);
}
