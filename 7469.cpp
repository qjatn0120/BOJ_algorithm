#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

vector <int> node[MX * 4];
int N, M, arr[MX], A, B, C;

void make_tree(int n, int L, int R){
    if(L == R){
        node[n].push_back(arr[L]);
        return;
    }
    int mid = L + R >> 1;
    make_tree(n * 2, L, mid);
    make_tree(n * 2 + 1, mid + 1, R);
    int p1 = 0, p2 = 0;
    while(p1 != node[n * 2].size() || p2 != node[n * 2 + 1].size()){
        if(p1 == node[n * 2].size()) node[n].push_back(node[n * 2 + 1][p2++]);
        else if(p2 == node[n * 2 + 1].size()) node[n].push_back(node[n * 2][p1++]);
        else{
            if(node[n * 2][p1] < node[n * 2 + 1][p2]) node[n].push_back(node[n * 2][p1++]);
            else node[n].push_back(node[n * 2 + 1][p2++]);
        }
    }
}

int Query_(int n, int L, int R, int a, int b, int k){
    if(L == a && R == b) return upper_bound(node[n].begin(), node[n].end(), k) - node[n].begin();
    int mid = L + R >> 1;
    if(b <= mid) return Query_(n * 2, L, mid, a, b, k);
    if(a > mid) return Query_(n * 2 + 1, mid + 1, R, a, b, k);
    return Query_(n * 2, L, mid, a, mid, k) + Query_(n * 2 + 1, mid + 1, R, mid + 1, b, k);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) scanf("%d", &arr[i]);
    make_tree(1, 1, N);
    for(int i = 0; i < M; i++){
        scanf("%d %d %d", &A, &B, &C);
        int lo = -1e9, hi = 1e9;
        while(lo < hi){
            int mid = lo + hi >> 1;
            int cnt = Query_(1, 1, N, A, B, mid);
            if(cnt < C) lo = mid + 1;
            else hi = mid;
        }
        printf("%d\n", lo);
    }
}
