#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

int N, B, C;
long long int ans, sum, A[MX];

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> N >> B >> C;
    for(int i = 1; i <= N; i++) cin >> A[i], sum += A[i];
    if(B <= C) ans = sum * B;
    else{
        long long int tmp1 = 0, tmp2 = 0;
        for(int i = 1; i <= N; i++){
            long long int cnt1 = min(tmp1, A[i]);
            A[i] -= cnt1, ans += cnt1 * C;
            long long int cnt2 = min(tmp2, A[i]);
            A[i] -= cnt2, ans += cnt2 * C;
            ans += A[i] * B;
            tmp1 = A[i], tmp2 = cnt1;
        }
    }
    cout << ans;
}
