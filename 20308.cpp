#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

long long int W, H, L, N;

vector <long long int> query[MX * 2];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> W >> H >> L >> N;
    long long int x, y, w, h, p1, p2;
    for(int i = 0; i < N; i++){
        cin >> x >> y >> w >> h;
        if((y + h) * W < x * H) p1 = (y + h) * W / x + !!(((y + h) * W) % x);
        else p1 = W + H - H * x / (y + h);
        if(y * W < (x + w) * H) p2 = y * W / (x + w);
        else p2 = W + H - (H * (x + w) / y + !!((H * (x + w)) % y));
        if(p1 - p2 > L) continue;
        query[p1].push_back(w * h);
        query[p2].push_back(-w * h);
    }
    long long int Area = 0, ans = 0;
    for(int i = 0; i < L; i++){
        for(auto q : query[i]) Area += max(0LL, q);
    }
    for(int i = 0; i + L < W + H; i++){
        for(auto q : query[i + L]) Area += max(0LL, q);
        ans = max(ans, Area);
        for(auto q : query[i]) Area += min(0LL, q);
    }
    cout << ans;
}
