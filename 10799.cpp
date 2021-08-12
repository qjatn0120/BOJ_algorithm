#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

string s;
bool lazer[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> s;
    for(int i = 0; i < (int)s.size() - 1; i++){
        if(s[i] == '(' && s[i + 1] == ')') lazer[i] = lazer[i + 1] = true;
    }

    int cnt = 0, ans = 0;
    for(int i = 0; i < (int)s.size(); i++){
        if(lazer[i]){
            if(s[i] == '(') ans += cnt;
        }else if(s[i] == '('){
            ans++;
            cnt++;
        }else{
            cnt--;
        }
    }
    cout << ans;
}
