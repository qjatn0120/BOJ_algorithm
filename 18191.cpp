#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

int N, M, K, P[MX];

bool able(int L){
    long long int S = 1, E = N;
    for(int i = 2; i <= M; i++){
        long long int D = P[i] - P[i - 1];
        int pL = ceil((double)(-L - D) / K), pR = floor((double)(L - D) / K);
        if(pL > pR) return false;
        S = max(1LL, S + pL), E = min((long long)N, E + pR);
        if(S > E) return false;
    }
    return true;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M >> K;
    for(int i = 1; i <= M; i++) cin >> P[i];
    int lo = 0, hi = 1e9;
    while(lo < hi){
        int mid = (lo + hi) >> 1;
        if(able(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << hi;
}
