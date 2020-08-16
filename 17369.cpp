#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

struct Obj{
    int x, y, type;
    int next[4];

    Obj(int x, int y, int type) : x(x), y(y), type(type){
        for(int i = 0; i < 4; i++) next[i] = -1;
    }
};

vector <Obj> obj;
vector <pair<int, int> > row[MX], col[MX];

int N, M, K, Q, x, y;
pair <int, long long int> mem[MX * 4];

char c;

int main(){
    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for(int i = 0; i < K; i++){
        scanf("%d %d %c\n", &y, &x, &c);
        int C;
        if(c == '/') C = 1;
        else if(c == '\\') C = 2;
        else C = 3;
        row[y].push_back({x, (int)obj.size()});
        col[x].push_back({y, (int)obj.size()});
        obj.push_back(Obj(x, y, C));
    }
    for(int i = 1; i <= N; i++){
        row[i].push_back({0, (int)obj.size()});
        obj.push_back(Obj(0, i, 0));
        row[i].push_back({M + 1, (int)obj.size()});
        obj.push_back((Obj(M + 1, i, 0)));
    }
    for(int i = 1; i <= M; i++){
        col[i].push_back({0, (int)obj.size()});
        obj.push_back(Obj(i, 0, 0));
        col[i].push_back({N + 1, (int)obj.size()});
        obj.push_back(Obj(i, N + 1, 0));
    }
    for(int i = 1; i <= N; i++) sort(row[i].begin(), row[i].end());
    for(int i = 1; i <= M; i++) sort(col[i].begin(), col[i].end());
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < (int)row[i].size() - 1; j++){
            int Lidx = row[i][j].second, Ridx = row[i][j + 1].second;
            obj[Lidx].next[1] = Ridx;
            obj[Ridx].next[3] = Lidx;
        }
    }
    for(int i = 1; i <= M; i++){
        for(int j = 0; j < (int)col[i].size() - 1; j++){
            int Uidx = col[i][j].second, Didx = col[i][j + 1].second;
            obj[Uidx].next[2] = Didx;
            obj[Didx].next[0] = Uidx;
        }
    }
    for(int i = 0; i < MX * 4; i++) mem[i].first = -1;
    while(Q--){
        scanf("%c%d\n", &c, &x);
        int init, pos, dir, initDir;
        if(c == 'D') init = col[x].back().second, dir = 0;
        else if(c == 'U') init = col[x].front().second, dir = 2;
        else if(c == 'L') init = row[x].front().second, dir = 1;
        else init = row[x].back().second, dir = 3;
        initDir = dir;
        if(mem[x * 4 + initDir].first == -1){
            pos = obj[init].next[dir];
            long long int dist, sum = 0;
            int cnt = 0;
            dist = abs(obj[init].x - obj[pos].x) + abs(obj[init].y - obj[pos].y);
            while(obj[pos].type){
                if(obj[pos].type == 1){
                    int arr[4] = {1, 0, 3, 2};
                    dir = arr[dir];
                }else if(obj[pos].type == 2){
                    int arr[4] = {3, 2, 1, 0};
                    dir = arr[dir];
                }else{
                    cnt++;
                    sum += dist;
                }
                int next = obj[pos].next[dir];
                dist += abs(obj[pos].x - obj[next].x) + abs(obj[pos].y - obj[next].y);
                pos = next;
            }
            mem[x * 4 + initDir] = {cnt, sum};
        }
        printf("%d %lld\n", mem[x * 4 + initDir].first, mem[x * 4 + initDir].second);
    }
}
