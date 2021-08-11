#include <bits/stdc++.h>

using namespace std;

long long int mod = 1e9 + 7;
long long int dp[5005];
int T, E;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    dp[0] = dp[1] = 1;
    for(int i = 2; i <= 5001; i++){
        for(int j = 0; j < i; j++) dp[i] = (dp[i] + dp[j] * dp[i - 1 - j]) % mod;
    }

    cin >> T;
    while(T--){
        cin >> E;
        cout << dp[E + 1] << "\n";
    }
}
