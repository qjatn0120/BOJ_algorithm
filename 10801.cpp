#include <bits/stdc++.h>

using namespace std;

int a[10], b[10];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    for(int i = 0; i < 10; i++) cin >> a[i];
    for(int i = 0; i < 10; i++) cin >> b[i];
    int ans = 0;
    for(int i = 0; i < 10; i++){
        if(a[i] > b[i]) ans++;
        if(a[i] < b[i]) ans--;
    }

    if(ans < 0) cout << 'B';
    else if(ans > 0) cout << 'A';
    else cout << 'D';
}
