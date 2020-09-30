#include <bits/stdc++.h>

using namespace std;

int N, X[20], ans;

void f(int n){
    if(n == N){
        ans++;
        return;
    }
    for(int i = 0; i < N; i++){//(i, n)
        bool able = true;
        for(int j = 0; j < n; j++){
            if(X[j] == i || j - X[j] == n - i || j + X[j] == n + i) able = false;
        }
        if(!able) continue;
        X[n] = i;
        f(n + 1);
    }
}

int main(){
    scanf("%d", &N);
    f(0);
    printf("%d", ans);
}
