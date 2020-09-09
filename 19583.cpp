#include <bits/stdc++.h>

using namespace std;

string s;

int getTime(){
    cin >> s;
    if(cin.eof()) return -1;
    int h = (s[0] - '0') * 10 + (s[1] - '0');
    int m = (s[3] - '0') * 10 + (s[4] - '0');
    return h * 60 + m;
}

int S, E, Q, ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    S = getTime(), E = getTime(), Q = getTime();
    map <string, bool> mp;
    while(1){
        int T = getTime();
        if(cin.eof()) break;
        cin >> s;
        if(T <= S) mp.insert({s, false});
        if(E <= T && T <= Q){
            if(mp.find(s) != mp.end()) mp[s] = true;
        }
    }
    for(auto i : mp) ans += i.second;
    cout << ans;
}
