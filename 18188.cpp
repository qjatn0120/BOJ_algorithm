#include <bits/stdc++.h>

using namespace std;

const int MX = 22;
const int dir_x[4] = {0, -1, 0, 1}, dir_y[4] = {-1, 0, 1, 0};

int H, W, N, dir[MX][2], bef[MX][MX][MX];
pair <int, int> S, E;
bool arr[MX][MX];
string str;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> H >> W;
    for(int i = 0; i < H; i++){
        cin >> str;
        for(int j = 0; j < W; j++){
            arr[i][j] = str[j] == '@';
            if(str[j] == 'D') S = {i, j};
            if(str[j] == 'Z') E = {i, j};
        }
    }
    cin >> N;
    char c1, c2;
    for(int i = 0; i < N; i++){
        cin >> c1 >> c2;
        char c[4] = {'W', 'A', 'S', 'D'};
        dir[i][0] = find(c, c + 4, c1) - c;
        dir[i][1] = find(c, c + 4, c2) - c;
    }
    queue <pair<int, int> > q;
    q.push(S);
    int p;
    for(p = 0; p < N; p++){
        int sz = q.size();
        while(sz--){
            auto tmp = q.front();
            q.pop();
            for(int d = 0; d < 4; d++){
                if(d == dir[p][0] || d == dir[p][1]){
                    int py = tmp.first + dir_y[d], px = tmp.second + dir_x[d];
                    if(px < 0 || px >= W || py < 0 || py >= H || arr[py][px]) continue;
                    bef[p][py][px] = d + 1;
                    q.push({py, px});
                }
            }
        }
        if(bef[p][E.first][E.second]) break;
    }
    if(!bef[p][E.first][E.second]) cout << "NO";
    else{
        string ans = "";
        while(p >= 0){
            if(bef[p][E.first][E.second] == 1) ans += "W", E.first++;
            else if(bef[p][E.first][E.second] == 2) ans += "A", E.second++;
            else if(bef[p][E.first][E.second] == 3) ans += "S", E.first--;
            else if(bef[p][E.first][E.second] == 4) ans += "D", E.second--;
            p--;
        }
        reverse(ans.begin(), ans.end());
        cout << "YES\n" << ans;
    }
}
