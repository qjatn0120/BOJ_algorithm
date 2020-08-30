#include <bits/stdc++.h>

using namespace std;

const int MX = 100005;

string s;
int g[MX], tg[MX], SA[MX];

struct cmp{
    int t;
    cmp(int t) : t(t){}
    bool operator ()(int x, int y){
        if(g[x] == g[y]) return g[x + t] < g[y + t];
        return g[x] < g[y];
    }
};

void GetSA(){
    for(int i = 0; i < s.size(); i++) g[i] = s[i] - 'a', SA[i] = i;
    for(int t = 1; t <= s.size(); t <<= 1){
        sort(SA, SA + s.size(), cmp(t));
        tg[SA[0]] = 1;
        for(int i = 1; i < s.size(); i++) tg[SA[i]] = tg[SA[i - 1]] + cmp(t).operator()(SA[i - 1], SA[i]);
        copy(tg, tg + s.size(), g);
    }
}

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> s;
    GetSA();
    for(int i = 0; i < s.size(); i++) cout << SA[i] << "\n";
}
