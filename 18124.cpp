#include <bits/stdc++.h>

using namespace std;

long long int N;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    if(N <= 2){
        cout << (N - 1);
        return 0;
    }
    long long int tmp = 1;
    while(tmp * 2 < N) tmp *= 2;
    cout << (tmp - 1 + (N + 1) / 2);
}
