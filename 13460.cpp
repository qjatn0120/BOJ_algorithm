#include <bits/stdc++.h>

using namespace std;

const int inf = 987654321;
const int dir_x[4] = {0, 1, 0, -1};
const int dir_y[4] = {1, 0, -1, 0};

void moveBall(pair<int, int> &pR, pair<int, int> &pB, int dir);

int N, M, ans = inf;
bool board[12][12];
pair<int, int> R, B, H;
int cache[12][12][12][12];

int main(){
    scanf("%d %d\n", &N, &M);
    for(int j = 0; j < N; j++){
        string str;
        getline(cin, str);
        for(int i = 0; i < M; i++){
            if(str[i] == '#') board[i][j] = true;
            else board[i][j] = false;
            if(str[i] == 'B') B = {i, j};
            if(str[i] == 'R') R = {i, j};
            if(str[i] == 'O') H = {i, j};
        }
    }
    for(int i = 0; i < 12; i++)
    for(int j = 0; j < 12; j++)
    for(int k = 0; k < 12; k++)
    for(int l = 0; l < 12; l++) cache[i][j][k][l] = inf;
    queue<pair<pair<int, int>, pair<int, int> > > q;
    q.push({R, B});
    cache[R.first][R.second][B.first][B.second] = 0;
    while(q.size()){
        pair<int, int> pR = q.front().first;
        pair<int, int> pB = q.front().second;
        q.pop();
        for(int dir = 0; dir < 4; dir++){
            pair<int, int> tmpR = pR, tmpB = pB;
            moveBall(tmpR, tmpB, dir);
            if(cache[tmpR.first][tmpR.second][tmpB.first][tmpB.second] != inf) continue;
            cache[tmpR.first][tmpR.second][tmpB.first][tmpB.second] = cache[pR.first][pR.second][pB.first][pB.second] + 1;
            if(tmpR.first == 10 && tmpB.first != 10) ans = min(ans, cache[tmpR.first][tmpR.second][tmpB.first][tmpB.second]);
            if(tmpR.first != 10 && tmpB.first != 10) q.push({tmpR, tmpB});
        }
    }
    if(ans > 10) ans = -1;
    printf("%d", ans);
}

void moveBall(pair<int, int> &pR, pair<int, int> &pB, int dir){
    bool Rmove, Bmove;
    int px, py;
    while(1){
        Rmove = Bmove = false;
        if(pR.first != 10){
            px = pR.first + dir_x[dir];
            py = pR.second + dir_y[dir];
            if(!board[px][py] && !(px == pB.first && py == pB.second)) pR = {px, py}, Rmove = true;
            if(px == H.first && py == H.second) pR.first = 10;
        }
        if(pB.first != 10){
            px = pB.first + dir_x[dir];
            py = pB.second + dir_y[dir];
            if(!board[px][py] && !(px == pR.first && py == pR.second)) pB = {px, py}, Bmove = true;
            if(px == H.first && py == H.second) pB.first = 10;
        }
        if(!Rmove && !Bmove) break;
    }
}
