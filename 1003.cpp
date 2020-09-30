#include <bits/stdc++.h>

using namespace std;

const int MX = 105;

int T, N, ans0, ans1;
pair <int, int> cache[MX];

pair <int, int> operator+(pair<int, int> a, pair<int, int> b){
    return {a.first + b.first, a.second + b.second};
}

pair <int, int> f(int n){
    if(cache[n].first || cache[n].second) return cache[n];
    if(n == 0) return {1, 0};
    if(n == 1) return {0, 1};
    return cache[n] = f(n - 1) + f(n - 2);
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        auto ans = f(N);
        printf("%d %d\n", ans.first, ans.second);
    }
}
