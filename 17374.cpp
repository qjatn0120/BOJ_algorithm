#include <bits/stdc++.h>

using namespace std;

int T;
long long int P, Q, A, B, C, D;

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%lld %lld %lld %lld %lld %lld", &P, &Q, &A, &B, &C, &D);
        int bit = P, coin = (Q / C) * D;
        int x = (bit - coin) / (A + B);
        long long int ans = min(bit - A * x, coin + B * x);
        x++;
        ans = max(ans, min(bit - A * x, coin + B * x));
        x -= 2;
        ans = max(ans, min(bit - A * x, coin + B * x));
        printf("%lld\n", ans);
    }
}
