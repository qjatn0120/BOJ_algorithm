#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

void make_tree1(int n, int L, int R);//min tree
void make_tree2(int n, int L, int R);//max tree
int Query1(int n, int L, int R, int a, int b);//min Query
int Query2(int n, int L, int R, int a, int b);//max Query

int node1[MX * 4], node2[MX * 4];
int N, M, arr[MX], A, B;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    make_tree1(1, 1, N);
    make_tree2(1, 1, N);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &A, &B);
        printf("%d %d\n", Query1(1, 1, N, A, B), Query2(1, 1, N, A, B));
    }
}

void make_tree1(int n, int L, int R){
    if(L == R){
        node1[n] = arr[L];
        return;
    }
    int mid = L + R >> 1;
    make_tree1(n * 2, L, mid);
    make_tree1(n * 2 + 1, mid + 1, R);
    node1[n] = min(node1[n * 2], node1[n * 2 + 1]);
}

void make_tree2(int n, int L, int R){
    if(L == R){
        node2[n] = arr[L];
        return;
    }
    int mid = L + R >> 1;
    make_tree2(n * 2, L, mid);
    make_tree2(n * 2 + 1, mid + 1, R);
    node2[n] = max(node2[n * 2], node2[n * 2 + 1]);
}

int Query1(int n, int L, int R, int a, int b){
    if(L == a && R == b) return node1[n];
    int mid = L + R >> 1;
    if(b <= mid) return Query1(n * 2, L, mid, a, b);
    if(a > mid) return Query1(n * 2 + 1, mid + 1, R, a, b);
    return min(Query1(n * 2, L, mid, a, mid), Query1(n * 2 + 1, mid + 1, R, mid + 1, b));
}

int Query2(int n, int L, int R, int a, int b){
    if(L == a && R == b) return node2[n];
    int mid = L + R >> 1;
    if(b <= mid) return Query2(n * 2, L, mid, a, b);
    if(a > mid) return Query2(n * 2 + 1, mid + 1, R, a, b);
    return max(Query2(n * 2, L, mid, a, mid), Query2(n * 2 + 1, mid + 1, R, mid + 1, b));
}
