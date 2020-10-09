#include <bits/stdc++.h>

using namespace std;

const int MX = 105;
const int inf = 987654321;
const int dir_x[4] = {-1, 0, 1, 0}, dir_y[4] = {0, 1, 0, -1};

int T, H, W, O, F, Xs, Ys, Xe, Ye, x, y, l;
int L[MX][MX], visited[MX][MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> T;
    while(T--){
        cin >> H >> W >> O >> F >> Ys >> Xs >> Ye >> Xe;
        Xs--, Ys--, Xe--, Ye--;
        for(int j = 0; j < H; j++)
        for(int i = 0; i < W; i++) L[j][i] = 0, visited[j][i] = -1;
        for(int i = 0; i < O; i++){
            cin >> y >> x >> l;
            L[y - 1][x - 1] = l;
        }
        queue <int> q;
        q.push(Ys * W + Xs);
        visited[Ys][Xs] = F;
        while(!q.empty()){
            int pos = q.front();
            q.pop();
            int X = pos % W, Y = pos / W;
            for(int dir = 0; dir < 4; dir++){
                int pX = X + dir_x[dir], pY = Y + dir_y[dir];
                if(pX < 0 || pX >= W || pY < 0 || pY >= H) continue;
                if(visited[pY][pX] != -1) continue;
                if(L[pY][pX] - L[Y][X] <= visited[Y][X]){
                    visited[pY][pX] = visited[Y][X] - 1;
                    if(visited[pY][pX]) q.push({pY * W + pX});
                }
            }
        }
        cout << (visited[Ye][Xe] != -1 ? "잘했어!!\n" : "인성 문제있어??\n");
    }
}
