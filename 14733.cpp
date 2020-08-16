#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 987654321;

map <int, int> comp_x;
vector <int> coord_x;

struct Seg{
    int y, x1, x2;
    bool add;
    Seg(int y, int x1, int x2, bool b) : y(y), x1(x1), x2(x2), add(b) {}
};

vector <Seg> v;

bool cmp(Seg p, Seg q){return p.y < q.y;}

int N, x1, x2, y1, y2;
int cnt[6005];
long long int ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        v.push_back(Seg(y1, x1, x2, true));
        v.push_back(Seg(y2, x1, x2, false));
        comp_x[x1] = comp_x[x2] = 0;
    }
    sort(v.begin(), v.end(), cmp);
    int tmp = 0;
    for(auto it = comp_x.begin(); it != comp_x.end(); it++){
        it->second = tmp++;
        coord_x.push_back(it->first);
    }
    for(int i = 0; i < v.size(); i++) v[i].x1 = comp_x[v[i].x1], v[i].x2 = comp_x[v[i].x2];
    int H = -inf;
    for(int i = 0; i < v.size(); i++){
        long long int sum = 0;
        for(int j = 0; j < (int)coord_x.size() - 1; j++){
            if(cnt[j]) sum += coord_x[j + 1] - coord_x[j];
        }
        if(H != inf) ans += (v[i].y - H) * sum;
        H = v[i].y;
        tmp = v[i].add ? 1 : -1;
        for(int j = v[i].x1; j < v[i].x2; j++) cnt[j] += tmp;
    }
    printf("%lld", ans);
}
