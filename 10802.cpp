#include <bits/stdc++.h>

using namespace std;

const int mod = 20150523;
const int MX = 1e5 + 5;

int dp[MX][2][2][3];
// dp[i][fit][use 369][sum % 3]
string str;

int isClap(string &s){
    int sum = 0;
    for(char c : s){
        int num = c - '0';
        sum += num;
        if(num % 3 == 0 && num) return 1;
    }
    if(sum % 3 == 0) return 1;
    return 0;
}

int solve(string &s){
    memset(dp, 0, sizeof(dp));
    dp[0][1][0][0] = 1;
    int sum = 0;
    int is3 = 0;

    for(int i = 1; i <= (int)s.size(); i++){
        int num = s[i - 1] - '0';

        // dp[i][x fit][x use 369]
        for(int j = 0; j < 10; j++){
            if(j % 3 == 0 && j) continue;
            for(int k = 0; k < 3; k++){
                dp[i][0][0][(k + j) % 3] = (dp[i][0][0][(k + j) % 3] + dp[i - 1][0][0][k]) % mod;
                if(j < num) dp[i][0][0][(k + j) % 3] = (dp[i][0][0][(k + j) % 3] + dp[i - 1][1][0][k]) % mod;
            }
        }


        // dp[i][x fit][use 369]
        for(int j = 0; j < 10; j++){
            for(int k = 0; k < 3; k++){
                dp[i][0][1][(k + j) % 3] = (dp[i][0][1][(k + j) % 3] + dp[i - 1][0][1][k]) % mod;
                if(j % 3 == 0 && j) dp[i][0][1][(k + j) % 3] = (dp[i][0][1][(k + j) % 3] + dp[i - 1][0][0][k]) % mod;
                if(j < num){
                    dp[i][0][1][(k + j) % 3] = (dp[i][0][1][(k + j) % 3] + dp[i - 1][1][1][k]) % mod;
                    if(j % 3 == 0 && j) dp[i][0][1][(k + j) % 3] = (dp[i][0][1][(k + j) % 3] + dp[i - 1][1][0][k]) % mod;
                }
            }
        }

        // dp[i][fit]
        sum = (sum + num) % 3;
        if(num % 3 == 0 && num) is3 = 1;
        dp[i][1][is3][sum] = 1;
    }

    int ret = 0;
    for(int i = 0; i < 2; i++)
    for(int j = 0; j < 2; j++)
    for(int k = 0; k < 3; k++){
        if(j == 1 || k == 0) ret = (ret + dp[(int)s.size()][i][j][k]) % mod;
    }
    return ret - 1; // 0 제외
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> str;
    int ans = -solve(str) + isClap(str);
    cin >> str;
    ans = (ans + solve(str) + mod) % mod;
    cout << ans;
}
