#include <bits/stdc++.h>

using namespace std;

int N, K;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> K;
    cout << "YES\n";
    if((1 << N) == K) cout << "0 ", K--;
    for(int i = 0; K; i++){
        if(K & 1){
            for(int j = (1 << i); j < (1 << i + 1); j++) cout << j << " ";
        }
        K >>= 1;
    }
}
