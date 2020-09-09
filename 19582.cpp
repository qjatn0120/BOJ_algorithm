#include <bits/stdc++.h>

using namespace std;

const long long int inf = LONG_LONG_MAX / 10;
const int MX = 1e5 + 5;

int N;
long long int X[MX], P[MX], DP[MX][2];

int main(){
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> X[i] >> P[i];
    for(int i = 1; i <= N; i++){
        DP[i][0] = DP[i][1] = inf;
        DP[i][1] = DP[i - 1][0];
        if(DP[i - 1][0] <= X[i]) DP[i][0] = DP[i - 1][0] + P[i];
        if(DP[i - 1][1] <= X[i]) DP[i][1] = min(DP[i][1], DP[i - 1][1] + P[i]);
    }
    cout << (DP[N][1] == inf ? "Zzz" : "Kkeo-eok");
}
