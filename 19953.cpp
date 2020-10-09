#include <bits/stdc++.h>

using namespace std;

const int dir_x[4] = {1, 0, -1, 0}, dir_y[4] = {0, -1, 0, 1};

long long int x, y;
int v, m, t;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> y >> m >> t;
    v = (y * m) % 10, t--;
    vector <int> cycle;
    set <int> s;
    while(1){
        auto ret = s.insert(v);
        if(!ret.second) break;
        cycle.push_back(v);
        v = (v * m) % 10;
    }
    long long int pX = 0, pY = 0;
    int sz = (int)cycle.size() * 4;
    for(int i = 0; i < sz; i++){
        pX += cycle[i % cycle.size()] * dir_x[i % 4];
        pY += cycle[i % cycle.size()] * dir_y[i % 4];
    }
    x += pX * (t / sz), y += pY * (t / sz), t %= sz;
    for(int i = 0; i < t; i++){
        x += cycle[i % cycle.size()] * dir_x[i % 4];
        y += cycle[i % cycle.size()] * dir_y[i % 4];

    }
    cout << x << " " << y;
}
