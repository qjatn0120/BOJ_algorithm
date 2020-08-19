#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

char str[MX];
int N, SA[MX], LCP[MX], g[MX], tg[MX];

struct cmp{
    cmp(int t) : t(t) {}
    int t;
    bool operator ()(int x, int y){
        if(g[x] == g[y]) return g[x + t] < g[y + t];
        return g[x] < g[y];
    }
};

void getSA(){
    int sz = strlen(str);
    for(int i = 0; i < sz; i++) SA[i] = i, g[i] = str[i] - 'a' + 1;
    for(int t = 1; t <= sz; t <<= 1){
        sort(SA, SA + sz, cmp(t));
        tg[SA[0]] = 1;
        for(int i = 1; i < sz; i++) tg[SA[i]] = tg[SA[i - 1]] + cmp(t).operator()(SA[i - 1], SA[i]);
        copy(tg, tg + sz, g);
    }
}

void getLCP(){
    int Rank[MX], sz = strlen(str), len = 0;
    for(int i = 0; i < sz; i++) Rank[SA[i]] = i;
    for(int i = 0; i < sz; i++){
        int tar = Rank[i];
        if(tar){
            int j = SA[tar - 1];
            while(str[i + len] == str[j + len]) len++;
            LCP[tar] = len;
            len = max(0, len - 1);
        }
    }
}

int main(){
    cin >> N >> str;
    getSA();
    getLCP();
    printf("%d", *max_element(LCP, LCP + strlen(str)));
}
