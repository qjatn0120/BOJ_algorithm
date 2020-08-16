#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct query{
    int y, x1, x2;
    bool add;
    query(int y, int x1, int x2, bool b) : y(y), x1(x1), x2(x2), add(b) {}
};

bool cmp(query a, query b){
    if(a.y == b.y) return a.add < b.add;
    return a.y > b.y;
}

int T, n, w, h, x1, x2, y1, y2, w_, h_;

vector <query> v;
vector <int> coord_X;
vector <int> gap;
map <int, int> comp_x;
pair<int, int> ans;
int height[505];

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d %d", &n, &w, &h);
        comp_x.clear();
        v.clear();
        gap.clear();
        coord_X.clear();
        for(int i = 0; i < n; i++){
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            v.push_back(query(y2, x1, x2, true));
            v.push_back(query(y1, x1, x2, false));
            comp_x.insert({x1, 0});
            comp_x.insert({x2, 0});
        }
        v.push_back(query(0, 0, 0, true));
        sort(v.begin(), v.end(), cmp);
        scanf("%d %d", &w_, &h_);
        comp_x.insert({0, 0});
        comp_x.insert({w, 0});
        int cnt = 0;
        for(auto it = comp_x.begin(); it != comp_x.end(); it++){
            it->second = cnt++;
            coord_X.push_back(it->first);
        }
        for(int i = 0; i < (int)coord_X.size() - 1; i++) gap.push_back(coord_X[i + 1] - coord_X[i]);
        for(int i = 0; i < v.size(); i++){
            v[i].x1 = comp_x[v[i].x1];
            v[i].x2 = comp_x[v[i].x2];
        }
        int H = h;
        ans.first = -1;
        for(int i = 0; i < gap.size(); i++) height[i] = 0;
        for(int i = 0; i < v.size(); i++){
            for(int j = 0; j < gap.size(); j++) if(height[j] != -1) height[j] += H - v[i].y;
            H = v[i].y;
            int tarX = 0, sum = 0;
            for(int j = 0; j < gap.size(); j++){
                if(height[j] >= h_){
                    sum += gap[j];
                    if(sum >= w_) break;
                }else{
                    tarX = j + 1;
                    sum = 0;
                }
            }
            if(sum >= w_) ans = {coord_X[tarX], H};
            for(int j = v[i].x1; j < v[i].x2; j++) height[j] = v[i].add ? -1 : 0;
        }
        if(ans.first == -1) printf("Fail!\n");
        else printf("%d %d\n", ans.first, ans.second);
    }
}
