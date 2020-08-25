#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;
const long long int MOD = 1e9 + 7;
long long int N, x, w[MX], A, I, ans;

int main(){
    scanf("%lld %lld", &N, &x);
    w[0] = 1;
    for(int i = 1; i < MX; i++) w[i] = (w[i - 1] * x) % MOD;
    for(int i = 0; i <= N; i++){
        scanf("%lld %lld", &A, &I);
        ans = (ans + A * w[I]) % MOD;
    }
    printf("%lld", ans);
}
