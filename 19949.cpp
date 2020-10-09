#include <bits/stdc++.h>

using namespace std;

short A[10], ans[10], corr;
int cnt;

void check(int N){
    if(N == 10){
        if(corr >= 5) cnt++;
        return;
    }
    for(int i = 1; i <= 5; i++){
        ans[N] = i;
        if(N >= 2 && i == ans[N - 1] && ans[N - 1] == ans[N - 2]) continue;
        if(A[N] == i) corr++;
        check(N + 1);
        if(A[N] == i) corr--;
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    for(int i = 0; i < 10; i++) cin >> A[i];
    check(0);
    cout << cnt;
}
