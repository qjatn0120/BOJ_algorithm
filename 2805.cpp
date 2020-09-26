#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

int N, M;
int arr[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> arr[i];
    long long int lo = 0, hi = INT_MAX;
    while(lo < hi){
        long long int mid = lo + hi + 1 >> 1, sum = 0;
        for(int i = 0; i < N; i++) sum += max(0LL, arr[i] - mid);
        if(sum >= M) lo = mid;
        else hi = mid - 1;
    }
    cout << lo;
}
