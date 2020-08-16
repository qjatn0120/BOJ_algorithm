#include <bits/stdc++.h>

using namespace std;

map <string, int> mp;

const int MX = 55 * 55;

bool adj[MX][MX], able[MX][MX];
int N, M, bef[MX];
long long int cnt[MX];
string str1, str2;

void add(string s){
    auto ret = mp.insert({s, 0});
    if(ret.second) ret.first->second = mp.size();
}

void chk(int st, int p){
    able[st][p] = true;
    for(int i = 1; i <= N; i++){
        if(adj[p][i] && !able[st][i]) chk(st, i);
    }
}

int main(){
    cin >> N;
    while(N--){
        cin >> str1 >> M;
        add(str1);
        while(M--) cin >> str2, add(str2), adj[mp[str2]][mp[str1]] = true;
    }
    cin >> str1, N = mp.size();
    for(int i = 1; i <= N; i++) cnt[i] = 1;
    for(int i = 1; i <= N; i++) chk(i, i);
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++){
        if(able[i][j] && able[j][i]) adj[i][j] = false;
        if(adj[i][j]) bef[j]++;
    }
    queue <int> q;
    for(int i = 1; i <= N; i++) if(!bef[i]) q.push(i);
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(int i = 1; i <= N; i++){
            if(!adj[pos][i]) continue;
            cnt[i] += cnt[pos], bef[i]--;
            if(!bef[i]) q.push(i);
        }
    }
    printf("%lld", cnt[mp[str1]]);
}
