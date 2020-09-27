#include <bits/stdc++.h>

using namespace std;

int N, K, A[10], ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> K;
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = N - 1; i >= 0; i--){
        ans += K / A[i];
        K %= A[i];
    }
    cout << ans;
}
