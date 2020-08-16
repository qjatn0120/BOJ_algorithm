#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

long long int cnt[MX * 4];
int tree[MX * 4];

void update(int n, int nL, int nR, int L, int R, int dif){
    if(nL == L && nR == R) tree[n] += dif;
    else{
        int mid = nL + nR >> 1;
        if(L <= mid) update(n * 2, nL, mid, L, min(R, mid), dif);
        if(R > mid) update(n * 2 + 1, mid + 1, nR, max(mid + 1, L), R, dif);
    }
    if(tree[n]) cnt[n] = nR - nL + 1;
    else cnt[n] = cnt[n * 2] + cnt[n * 2 + 1];
}

struct Query{
    int x1, x2, y;
    int dif;
    Query(int x1, int x2, int y, int dif) : x1(x1), x2(x2), y(y), dif(dif) {}
};

bool cmp(Query q1, Query q2){
    if(q1.y == q2.y) return q1.dif > q2.dif;
    return q1.y < q2.y;
}

vector <Query> v1, v2;
int N, X1, X2, Y1, Y2;
long long int ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        X1 += 10000, X2 += 10000, Y1 += 10000, Y2 += 10000;
        if(X1 > X2) swap(X1, X2);
        if(Y1 > Y2) swap(Y1, Y2);
        v1.push_back(Query(X1, X2 - 1, Y1, 1));
        v1.push_back(Query(X1, X2 - 1, Y2, -1));
        v2.push_back(Query(Y1, Y2 - 1, X1, 1));
        v2.push_back(Query(Y1, Y2 - 1, X2, -1));
    }
    sort(v1.begin(), v1.end(), cmp);
    sort(v2.begin(), v2.end(), cmp);
    for(int i = 0; i < v1.size(); i++){
        int tmp = cnt[1];
        update(1, 1, MX, v1[i].x1, v1[i].x2, v1[i].dif);
        ans += abs(tmp - cnt[1]);
    }
    for(int i = 0; i < v2.size(); i++){
        int tmp = cnt[1];
        update(1, 1, MX, v2[i].x1, v2[i].x2, v2[i].dif);
        ans += abs(tmp - cnt[1]);
    }
    printf("%lld", ans);
}
