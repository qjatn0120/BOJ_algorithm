#include <bits/stdc++.h>

using namespace std;

int ans, init, board, n, m;
vector <int> target;
string str;
bool visited[1 << 28];

void getAns(int state);

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    for(int i = 0; i < 7; i++){
        int tmp = 0;
        for(int j = 0; j < 4; j++) tmp |= (1 << j * 7  + i);
        target.push_back(tmp);
        for(int j = 0; j < 4; j++) target.push_back(tmp ^ (1 << j * 7 + i));
    }
    for(int i = 0; i < 4; i++)
    for(int s = 0; s < 7; s++)
    for(int e = s + 2; e < 7; e++){
        int tmp = 0;
        for(int j = s; j <= e; j++) tmp |= (1 << i * 7 + j);
        target.push_back(tmp);
    }
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> str;
        int num = str.back() - '1', color = str.size() - 4;
        init |= (1 << color * 7 + num);
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> str;
        int num = str.back() - '1', color = str.size() - 4;
        board |= (1 << color * 7 + num);
    }
    ans = n;
    getAns(init | board);
    cout << n - ans;
}

void getAns(int state){
    if(visited[state]) return;
    visited[state] = true;
    if(!(state & board)) ans = min(ans, __builtin_popcount(state));
    for(int tar : target) if(!((state & tar) ^ tar)) getAns(state ^ tar);
}
