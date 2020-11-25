#include <bits/stdc++.h>

using namespace std;

int N, cnt = 1, ans = 1;

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++){
        ans += cnt;
        cnt += !!(i % 3);
    }
    printf("%d", ans);
}
