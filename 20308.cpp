#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

long long int W, H, L, N;
long long int q1[MX], q2[MX];

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
        q1[p1] += w * h;
        q2[p2] += -w * h;
    }
    long long int Area = 0, ans = 0;
    for(int i = 0; i < L; i++){
        Area += q1[i];
    }
    for(int i = 0; i + L < W + H; i++){
        Area += q1[i + L];
        ans = max(ans, Area);
        Area += q2[i];
    }
    cout << ans;
}
