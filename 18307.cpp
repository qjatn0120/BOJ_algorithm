#include <bits/stdc++.h>

using namespace std;

const int MX = 131073;
const double SQRT3 = sqrt(3);

struct Dot{
    int x, y;
    double d1, d2;
    int n;
    Dot(int x, int y) : x(x), y(y){
        d1 = x + y * SQRT3;
        d2 = x - y * SQRT3;
    }
};

bool cmp(Dot p1, Dot p2){
    return p1.d1 < p2.d1;
}

int tree[MX];

void update(int i){
    while(i < MX){
        tree[i]++;
        i += (i & -i);
    }
}

int query(int i){
    int ret = 0;
    while(i){
        ret += tree[i];
        i -= (i & -i);
    }
    return ret;
}

vector <Dot> v;
map <double, int> mp;

int n, x, y;
long long int ans;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d %d", &x, &y);
        v.push_back(Dot(x, y));
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < v.size(); i++) mp.insert({v[i].d2, 0});
    int cnt = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) it->second = ++cnt;
    for(int i = 0; i < v.size(); i++) v[i].n = mp[v[i].d2];
    for(int i = 0; i < v.size(); i++){
        ans += i - query(v[i].n);
        update(v[i].n);
    }
    printf("%lld", ans);
}
