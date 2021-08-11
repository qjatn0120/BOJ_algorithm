#include <bits/stdc++.h>

using namespace std;

int N, Q, P, K, C;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> Q;
    long long int idx = -1, ans = LLONG_MAX;

    for(int i = 0; i < N; i++){
        cin >> P >> K >> C;
        long long int cost = (Q - 1) / K;
        cost = cost * (cost + 1) / 2 * C + P;
        if(cost < ans) ans = cost, idx = i + 1;
    }
    cout << idx << " " << ans;
}
