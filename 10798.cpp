#include <bits/stdc++.h>

using namespace std;

string s[5];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    for(int i = 0; i < 5; i++) cin >> s[i];
    int sz = 0;
    for(int i = 0; i < 5; i++) sz = max(sz, (int)s[i].size());

    for(int i = 0; i < sz; i++){
        for(int j = 0; j < 5; j++){
            if(i < (int)s[j].size()) cout << s[j][i];
        }
    }
}
