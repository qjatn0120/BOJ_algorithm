#include <bits/stdc++.h>

using namespace std;

bool visited[60][60];
int N;

int visit(int a, int b, int t, int bef){
    if(visited[a][b]) return t == N;
    if(t == N) return 0;
    visited[a][b] = true;
    int ret = 0;
    if(bef != 0) ret += visit(a - 1, b, t + 1, 1);
    if(bef != 1) ret += visit(a + 1, b, t + 1, 0);
    if(bef != 2){
        if((a + b) & 1) ret += visit(a, b + 1, t + 1, 2);
        else ret += visit(a, b - 1, t + 1, 2);
    }
    visited[a][b] = false;
    return ret;
}

int main(){
    scanf("%d", &N);
    visited[30][29] = true;
    printf("%d", visit(30, 30, 0, 2));
}
