#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

int A, B, K, dist[MX], par[MX];

int Find(int a){if(a == par[a]) return a; return par[a] = Find(par[a]);}
void Union(int a, int b){
    if(a > b) swap(a, b);
    a = Find(a), b = Find(b);
    if(a == b) return;
    par[a] = b;
}

int main(){
    scanf("%d %d %d", &A, &B, &K);
    memset(dist, -1, sizeof(dist));
    for(int i = 0; i < MX; i++) par[i] = i;
    dist[A] = 0, B += A;
    Union(A, A + 2);
    queue <int> q;
    q.push(A);
    while(!q.empty()){
        int a = q.front(), b = B - q.front();
        q.pop();
        int L = a < K ? 2 * a - K : K, R = b < K ? 2 * b - K : K;
        for(int i = Find(a - L); i <= a + R; i = Find(i + 2)){
            dist[i] = dist[a] + 1;
            q.push(i);
            Union(i, i + 2);
        }
    }
    printf("%d", dist[0]);
}
