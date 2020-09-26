#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
int N, x[MX], ans = INT_MAX, p, q;

int main(){
    cin >> N;
    for(int i = 0; i < N; i++) cin >> x[i];
    sort(x, x + N);
    int p1 = 0, p2 = N - 1;
    while(p1 < p2){
        if(ans > abs(x[p1] + x[p2])) p = x[p1], q = x[p2], ans = abs(x[p1] + x[p2]);
        if(x[p2] + x[p1] < 0) p1++;
        else p2--;
    }
    cout << p << " " << q;
}
