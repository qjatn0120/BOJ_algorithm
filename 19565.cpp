#include <bits/stdc++.h>

using namespace std;

int N;

int main(){
    scanf("%d", &N);
    printf("%d\n", N * N + 1);
    printf("1 1 ");
    for(int i = 2; i <= N; i++){
        for(int j = i; j <= N; j++) printf("%d %d ", j, i);
        printf("1 ");
    }
}
