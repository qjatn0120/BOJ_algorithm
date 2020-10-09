#include <bits/stdc++.h>
#define POW2(x) ((x) * (x))

using namespace std;

int X1, Y1, Z1, X2, Y2, Z2, N, K, L1, L2;
bool able = true;
bitset <20001> DP;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    DP.reset();
    DP.flip(10000);
    cin >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2 >> N;
    int dist = POW2(X1 - X2) + POW2(Y1 - Y2) + POW2(Z1 - Z2);
    while(N--){
        cin >> K;
        L2 += K;
        DP = (DP << K) | (DP >> K);
    }
    for(int i = 10000; i <= 10000 + L2; i++){
        if(DP.test(i)){
            L1 = i - 10000;
            break;
        }
    }
    if(L1 * L1 > dist || L2 * L2 < dist) able = false;
    cout << (able ? "YES" : "NO");
}
