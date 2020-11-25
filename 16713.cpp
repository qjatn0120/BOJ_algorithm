#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

int N, Q, A, sum[MX], s, e, ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> A, sum[i] = sum[i - 1] ^ A;
    for(int i = 1; i <= Q; i++){
        cin >> s >> e;
        ans ^= (sum[s - 1] ^ sum[e]);
    }
    cout << ans;
}
