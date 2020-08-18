#include <bits/stdc++.h>

using namespace std;

string s;
int ans, p[5005];

int main(){
    cin >> s;
    while(s.size()){
        int j = 0;
        memset(p, 0, sizeof(p));
        for(int i = 1; i < s.size(); i++){
            while(j && s[i] != s[j]) j = p[j - 1];
            if(s[i] == s[j]) p[i] = ++j;
            ans = max(ans, p[i]);
        }
        s = s.substr(1, s.size());
    }
    printf("%d", ans);
}
