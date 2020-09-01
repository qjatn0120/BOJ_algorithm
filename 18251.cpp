#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5;

vector <int> v;
int N, W[MX];

long long int getMax(){
    long long int sum = 0, minSum = 0, ret = LONG_LONG_MIN;
    for(int i : v){
        sum += i;
        ret = max(ret, sum - minSum);
        minSum = min(minSum, sum);
    }
    return ret;
}

void DFS(int n){
    if(n > N) return;
    DFS(n * 2);
    v.push_back(W[n]);
    DFS(n * 2 + 1);
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) scanf("%d", &W[i]);
    long long int ans = LONG_LONG_MIN;
    while(N){
        int cnt = 1;
        for(int i = 1; i <= N; i++){
            DFS(i);
            if((i + 1) == (1 << cnt)) ans = max(ans, getMax()), v.clear(), cnt++;
        }
        N >>= 1;
    }
    printf("%lld", ans);
}
