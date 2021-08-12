#include <bits/stdc++.h>

using namespace std;

const int inf = 987654321;
int cache1[55][55], cache2[55][55][55][55];

int dp1(int a, int b){
    if(a == 0 || b == 0) return 0;
    if(cache1[a][b]) return cache1[a][b];
    if(a < b) return cache1[a][b] = dp1(b, a);
    if(a % b == 0) return cache1[a][b] = a / b;
    if(a > 5 * b) return cache1[a][b] = dp1(a - b, b) + 1;

    int ret = inf;
    for(int i = 1; i <= a / 2; i++) ret = min(ret, dp1(a - i, b) + dp1(i, b));
    for(int j = 1; j <= b / 2; j++) ret = min(ret, dp1(a, b - j) + dp1(a, j));
    return cache1[a][b] = ret;
}

int dp2(int h1, int w1, int h2, int w2){
    if(cache2[h1][w1][h2][w2]) return cache2[h1][w1][h2][w2];
    if(h1 == h2) return cache2[h1][w1][h2][w2] = dp1(h1, w1 - w2);
    if(w1 == w2) return cache2[h1][w1][h2][w2] = dp1(w1, h1 - h2);
    if(h2 == 0 || w2 == 0) return cache2[h1][w1][h2][w2] = dp1(h1, w1);

    int ret = inf;
    for(int cut = 1; cut <= h1 - h2; cut++) ret = min(ret, dp2(h1 - cut, w1, h2, w2) + dp1(cut, w1));
    for(int cut = 1; cut <= w1 - w2; cut++) ret = min(ret, dp2(h1, w1 - cut, h2, w2) + dp1(cut, h1));
    for(int cut = 1; cut <= h2; cut++) ret = min(ret, dp2(h1 - cut, w1, h2 - cut, w2) + dp1(cut, w1 - w2));
    for(int cut = 1; cut <= w2; cut++) ret = min(ret, dp2(h1, w1 - cut, h2, w2 - cut) + dp1(cut, h1 - h2));

    return cache2[h1][w1][h2][w2] = ret;
}

int h1, w1, h2, w2;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> h1 >> w1 >> h2 >> w2;
    cout << dp2(h1, w1, h2, w2);
}
