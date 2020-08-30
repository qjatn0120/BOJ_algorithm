#include <bits/stdc++.h>

using namespace std;

const int MOD = 10007, MX = 1005;

int cache[MX][MX];
string s;

int DP(int L, int R){
    if(L >= R) return L == R;
    if(cache[L][R]) return cache[L][R];
    int ret = DP(L + 1, R) + DP(L, R - 1) + 1;
    if(s[L] != s[R]) ret -= DP(L + 1, R - 1) + 1;
    return cache[L][R] = (ret + MOD) % MOD;
}

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> s;
    cout << DP(0, s.size() - 1);
}
