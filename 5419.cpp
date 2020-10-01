#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

long long int ans = 0;
int N, node[MX * 4], T;
pair <int, int> p[MX];
vector <int> x_comp, y_comp;

bool cmp(pair <int, int> a, pair <int, int> b){
    if(a.second == b.second) return a.first > b.first;
    return a.second < b.second;
}

void Update(int n, int L, int R, int tar){//arr[tar]++;
    if(L == R){
        node[n]++;
        return;
    }
    int mid = L + R >> 1;
    if(tar <= mid) Update(n * 2, L, mid, tar);
    else Update(n * 2 + 1, mid + 1, R, tar);
    node[n] = node[n * 2] + node[n * 2 + 1];
}

int Query(int n, int L, int R, int a, int b){//arr[a ~ b]
    if(L == a && R == b) return node[n];
    int mid = L + R >> 1;
    if(b <= mid) return Query(n * 2, L, mid, a, b);
    if(a > mid) return Query(n * 2 + 1, mid + 1, R, a, b);
    return Query(n * 2, L, mid, a, mid) + Query(n * 2 + 1, mid + 1, R, mid + 1, b);
}

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        memset(node, 0, sizeof(node));
        x_comp.clear();
        y_comp.clear();
        for(int i = 0; i < N; i++) scanf("%d %d", &p[i].first, &p[i].second);
        for(int i = 0; i < N; i++){
            x_comp.push_back(p[i].first);
            y_comp.push_back(p[i].second);
        }
        sort(x_comp.begin(), x_comp.end());
        sort(y_comp.begin(), y_comp.end());
        x_comp.erase(unique(x_comp.begin(), x_comp.end()), x_comp.end());
        y_comp.erase(unique(y_comp.begin(), y_comp.end()), y_comp.end());
        for(int i = 0; i < N; i++){
            p[i].first = lower_bound(x_comp.begin(), x_comp.end(), p[i].first) - x_comp.begin();
            p[i].second = lower_bound(y_comp.begin(), y_comp.end(), p[i].second) - y_comp.begin();
        }
        sort(p, p + N, cmp);
        ans = 0;
        for(int i = 0; i < N; i++){
            ans += Query(1, 0, x_comp.size() - 1, p[i].first, x_comp.size() - 1);
            Update(1, 0, x_comp.size() - 1, p[i].first);
        }
        printf("%lld\n", ans);
    }
}
