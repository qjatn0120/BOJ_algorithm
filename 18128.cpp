#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;

int dir_x[8] = {0, 1, 0, -1, -1, -1, 1, 1};
int dir_y[8] = {1, 0, -1, 0, -1, 1, -1, 1};

bool visited[MX][MX];
int arr[MX][MX], water[MX][MX];
int N, W, x, y;
string s;

bool test(int n){
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++) visited[i][j] = false;

    queue <pair<int, int> > q;
    q.push(make_pair(1, 1));
    visited[1][1] = true;
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        int x = p.first, y = p.second;
        for(int dir = 0; dir < 8; dir++){
            int nx = x + dir_x[dir], ny = y + dir_y[dir];
            if(nx < 1 || ny < 1 || nx > N || ny > N || !arr[nx][ny] || water[nx][ny] > n || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
        }
    }

    return visited[N][N - 1] | visited[N - 1][N] | visited[N - 1][N - 1];
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> W;
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= N; j++) water[i][j] = -1;

    queue <pair<int, int> > q;
    for(int i = 0; i < W; i++){
        cin >> x >> y;
        q.push(make_pair(x, y));
        water[x][y] = 0;
    }

    for(int i = 1; i <= N; i++){
        cin >> s;
        for(int j = 1; j <= N; j++){
            if(s[j - 1] == '0') arr[i][j] = 0;
            else arr[i][j] = 1;
        }
    }

    while(!q.empty()){
        auto p = q.front();
        q.pop();
        int x = p.first, y = p.second;
        for(int dir = 0; dir < 4; dir++){
            int nx = x + dir_x[dir], ny = y + dir_y[dir];
            if(nx < 1 || ny < 1 || nx > N || ny > N || water[nx][ny] != -1) continue;
            water[nx][ny] = water[x][y] + 1;
            q.push(make_pair(nx, ny));
        }
    }

    int lo = 0, hi = 2001;
    while(lo < hi){
        int mid = (lo + hi) >> 1;
        if(test(mid)) hi = mid;
        else lo = mid + 1;
    }

    if(lo == 2001) lo = -1;
    cout << lo;
}
