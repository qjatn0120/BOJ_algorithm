#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;
const int dir_x[4] = {0, 1, 0, -1}, dir_y[4] = {1, 0, -1, 0};

int N, H, W, M, K, m[MX], t[MX], a[MX], b[MX], u, x, y;
int R[10], board[505][505], unit[505][505], dist[505][505];

int main(){
    for(int j = 0; j < 505; j++)
    for(int i = 0; i < 505; i++) dist[i][j] = 200;
    scanf("%d %d %d", &N, &H, &W);
    for(int j = 0; j < H; j++)
    for(int i = 0; i < W; i++) scanf("%d", &board[i][j]);
    for(int i = 1; i <= N; i++) scanf("%d", &R[i]);
    for(int j = 0; j < H; j++)
    for(int i = 0; i < W; i++) board[i][j] = R[board[i][j]];
    scanf("%d", &M);
    for(int i = 1; i <= M; i++){
        scanf("%d %d %d %d", &m[i], &t[i], &a[i], &b[i]);
        unit[b[i]][a[i]] = i;
    }
    scanf("%d", &K);
    for(int i = 0; i < K; i++){
        scanf("%d %d %d", &u, &y, &x);
        if(board[x][y] == -1) continue;
        if(unit[x][y]) continue;
        priority_queue <pair<int, pair<int, int> > > pq;
        queue <pair<int, int> >moveList;
        pq.push({0, {b[u], a[u]}}), moveList.push({b[u], a[u]}), dist[b[u]][a[u]] = 0;
        while(pq.size()){
            int px = pq.top().second.first, py = pq.top().second.second;
            pq.pop();
            for(int dir = 0; dir < 4; dir++){
                int nx = px + dir_x[dir], ny = py + dir_y[dir];
                if(nx < 0 || ny < 0 || nx >= W || ny >= H) continue;
                if(unit[nx][ny] && t[unit[nx][ny]] != t[unit[b[u]][a[u]]]) continue;
                if(board[nx][ny] == -1) continue;
                int nDist = dist[px][py] + board[nx][ny];
                if(nDist > m[u]) continue;
                if(dist[nx][ny] <= nDist) continue;
                dist[nx][ny] = nDist, moveList.push({nx, ny});
                bool moveAble = true;
                for(int dir2 = 0; dir2 < 4; dir2++){
                    int nnx = nx + dir_x[dir2], nny = ny + dir_y[dir2];
                    if(nnx < 0 || nny < 0 || nnx >= W || nny >= H) continue;
                    if(unit[nnx][nny] && t[unit[nnx][nny]] != t[unit[b[u]][a[u]]]) moveAble = false;
                }
                if(moveAble) pq.push({-nDist, {nx, ny}});
            }
        }
        if(dist[x][y] != 200){
            unit[x][y] = unit[b[u]][a[u]];
            unit[b[u]][a[u]] = 0;
            b[u] = x, a[u] = y;
        }
        while(moveList.size()){
            int px = moveList.front().first, py = moveList.front().second;
            moveList.pop();
            dist[px][py] = 200;
        }
    }
    for(int i = 1; i <= M; i++) printf("%d %d\n", a[i], b[i]);
}
