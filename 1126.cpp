#include <bits/stdc++.h>

using namespace std;

int N, a[55];
int cache[55][500005];

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    for(int i = 0; i < 55; i++)
    for(int j = 0; j < 500005; j++) cache[i][j] = -1;
    cache[0][0] = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= 500000; j++){
            if(cache[i][j] == -1) continue;
            int A = cache[i][j] + a[i], B = cache[i][j] + j;
            if(A > B) swap(A, B);
            cache[i + 1][B - A] = max(cache[i + 1][B - A], A);
            A = cache[i][j], B = cache[i][j] + j + a[i];
            cache[i + 1][B - A] = max(cache[i + 1][B - A], A);
            A = cache[i][j], B = cache[i][j] + j;
            cache[i + 1][B - A] = max(cache[i + 1][B - A], A);
        }
    }
    int ans = -1;
    for(int i = 1; i <= N; i++){
        if(cache[i][0]) ans = max(ans, cache[i][0]);
    }
    printf("%d", ans);
}
