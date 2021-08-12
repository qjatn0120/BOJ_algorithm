#include <bits/stdc++.h>

using namespace std;

int N, n, ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 0; i < 5; i++){
        cin >> n;
        if(N == n) ans++;
    }
    cout << ans;
}
