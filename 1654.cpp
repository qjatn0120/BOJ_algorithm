#include <bits/stdc++.h>

using namespace std;

int N, K, m;
vector <int> v;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> K >> N;
    for(int i = 0; i < K; i++){
        cin >> m;
        v.push_back(m);
    }
    long long int lo = 1, hi = INT_MAX;
    while(lo < hi){
        long long int mid = lo + hi + 1 >> 1;
        long long int cnt = 0;
        for(int i : v) cnt += i / mid;
        if(cnt >= N) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}
