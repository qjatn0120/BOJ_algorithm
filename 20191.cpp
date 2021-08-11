#include <bits/stdc++.h>

using namespace std;

string S, T;
vector <int> pos[26];
int p, ans = 1;

bool exist[26];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> S >> T;

    for(char c : T){
        exist[c - 'a'] = true;
        pos[c - 'a'].push_back(p++);
    }

    p = -1;
    for(char c : S){
        if(!exist[c - 'a']){
            ans = -1;
            break;
        }

        auto it = upper_bound(pos[c - 'a'].begin(), pos[c - 'a'].end(), p);
        if(it == pos[c - 'a'].end()) it = pos[c - 'a'].begin(), ans++;
        p = (*it);
    }

    cout << ans;
}
