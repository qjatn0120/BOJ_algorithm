#include <bits/stdc++.h>

using namespace std;

string s, ans;
int K;
bool chk[26];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> s >> K;
    for(char &c : s){
        if(c >= 'a') c += 'A' - 'a';
    }

    char c = s[0];
    int cnt = 1;
    for(int i = 1; i < (int)s.size(); i++){
        if(c != s[i]){
            if(!chk[c - 'A']){
                chk[c - 'A'] = true;
                if(cnt < K) ans.push_back('0');
                else ans.push_back('1');
            }
            cnt = 1;
            c = s[i];
        }else cnt++;
    }

    if(!chk[c - 'A']){
        if(cnt < K) ans.push_back('0');
        else ans.push_back('1');
    }
    cout << ans;
}
