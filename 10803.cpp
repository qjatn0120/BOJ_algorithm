#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b){if(b == 0) return a; return gcd(b, a % b);}

int cache[10005][105];

int dp(int a, int b){
    if(cache[a][b]) return cache[a][b];
    if(a < b) return cache[a][b] = dp(b, a);
    if(a % b == 0) return cache[a][b] = a / b;
    if(a > 5 * b) return cache[a][b] = dp(a - b, b) + 1;

    int ret = a * b;
    for(int i = 1; i <= a / 2; i++) ret = min(ret, dp(a - i, b) + dp(i, b));
    for(int j = 1; j <= b / 2; j++) ret = min(ret, dp(a, b - j) + dp(a, j));
    return cache[a][b] = ret;

}

int N, M;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    cout << dp(N, M);
}
