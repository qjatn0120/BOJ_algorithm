#include <bits/stdc++.h>

using namespace std;

const double err = 1e-10;

struct pos{
    int x, y;
    bool isIn;
    double dir;
    pos(int x, int y) : x(x), y(y){
        isIn = y >= 0;
        if(y < 0) dir = atan2(-y, -x);
        else dir = atan2(y, x);
    }
};

struct cmp{
    bool b;
    cmp(bool b) : b(b){}
    bool operator() (pos p1, pos p2){
        if(abs(p1.dir - p2.dir) < err){
             if(b) return p1.isIn > p2.isIn;
             else return p1.isIn < p2.isIn;
        }
        return p1.dir < p2.dir;
    }
};

vector <pos> tree;
int N, W, H, x, y, cnt;

int main(){
    while(1){
        scanf("%d %d %d", &N, &W, &H);
        if(!N) break;
        tree.clear(), cnt = 0;
        for(int i = 0; i < N; i++){
            scanf("%d %d", &x, &y);
            tree.push_back(pos(2 * x - W, 2 * y - H));
            cnt += tree.back().isIn;
        }
        sort(tree.begin(), tree.end(), cmp(cnt > N / 2));
        for(int i = 0; i < tree.size() && cnt != N / 2; i++){
            if(tree[i].isIn) cnt--, tree[i].isIn = false;
            else cnt++, tree[i].isIn = true;
        }
        for(int i = 0; i < tree.size(); i++){
            if(tree[i].isIn) printf("%d %d\n", (tree[i].x + W) / 2, (tree[i].y + H) / 2);
        }
    }
}
