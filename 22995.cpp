#include <bits/stdc++.h>

using namespace std;

int T, K, ans[40];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> T;
    while(T--){
        cin >> K; K++;
        memset(ans, -1, sizeof(ans));
        int len;
        for(len = 0; (1 << len) <= K; len++);
        len--; K -= (1 << len);
        for(int i = 0; i < len; i++) ans[i * 2] = 100 + i;
        for(int i = 0; i < len; i++){
            if(K & (1 << i)) ans[len * 2 - 1 - i * 2] = 1 + i;
        }

        vector <int> res;
        for(int i = 0; i < 40; i++){
            if(ans[i] != -1) res.push_back(ans[i]);
        }

        cout << (int)res.size() << "\n";
        for(int i : res) cout << i << " ";
        cout << "\n";
    }
}
