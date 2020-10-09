#include <bits/stdc++.h>

using namespace std;

int cnt[27];
string str;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    getline(cin, str);
    cin >> cnt[26];
    for(int i = 0; i < 26; i++) cin >> cnt[i];
    string title = string(1, str[0]);
    for(int i = 1; i < str.size(); i++) if(str[i - 1] == ' ' && str[i] != ' ') title += string(1, str[i]);
    for(int i = 0; i < title.size(); i++) title[i] = toupper(title[i]);
    for(int i = 0; i < title.size(); i++){
        if(i && title[i] == title[i - 1]) continue;
        cnt[title[i] - 'A']--;
    }
    for(int i = 0; i < str.size(); i++){
        if(i && str[i] == str[i - 1]) continue;
        if(str[i] == ' ') cnt[26]--;
        else cnt[toupper(str[i]) - 'A']--;
    }
    bool chk = true;
    for(int i = 0; i < 27; i++) if(cnt[i] < 0) chk = false;
    cout << (chk ? title : "-1");
}
