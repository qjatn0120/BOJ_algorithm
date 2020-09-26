#include <bits/stdc++.h>

using namespace std;

const int MX = 1e9;
int N, C, x;
vector <int> v;

int main(){
    cin >> N >> C;
    for(int i = 0; i < N; i++) cin >> x, v.push_back(x);
    sort(v.begin(), v.end());
    int lo = 1, hi = MX;
    while(lo < hi){
        int mid = lo + hi + 1 >> 1;
        int pos = -MX, cnt = 0;
        for(int i = 0; i < N; i++){
            if(v[i] - pos >= mid) cnt++, pos = v[i];
        }
        if(cnt >= C) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}
