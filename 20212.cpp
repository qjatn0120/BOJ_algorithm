#include <bits/stdc++.h>

using namespace std;

const int MX = 200005;

typedef struct{
    int t, a, b, k, idx;
    long long int ans;
}query;

long long int Node[MX * 4], lazy[MX * 4], K;
vector <int> comp;

void prop(int n, int L, int R){
    if(!lazy[n]) return;
    if(L != R){
        lazy[n * 2] += lazy[n];
        lazy[n * 2 + 1] += lazy[n];
    }
    Node[n] += lazy[n] * (comp[R] - comp[L - 1]);
    lazy[n] = 0;
}


void Update(int n, int L, int R, int nL, int nR){
    if(L == nL && R == nR){
        lazy[n] += K;
        prop(n, nL, nR);
        return;
    }
    prop(n, nL, nR);
    int mid = nL + nR >> 1;
    if(R <= mid) Update(n * 2, L, R, nL, mid), prop(n * 2 + 1, mid + 1, nR);
    else if(L > mid) Update(n * 2 + 1, L, R, mid + 1, nR), prop(n * 2, nL, mid);
    else Update(n * 2, L, mid, nL, mid), Update(n * 2 + 1, mid + 1, R, mid + 1, nR);
    Node[n] = Node[n * 2] + Node[n * 2 + 1];
}

long long int Query(int n, int L, int R, int nL, int nR){
    prop(n, nL, nR);
    if(L == nL && R == nR) return Node[n];
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(n * 2, L, R, nL, mid);
    if(L > mid) return Query(n * 2 + 1, L, R, mid + 1, nR);
    return Query(n * 2, L, mid, nL, mid) + Query(n * 2 + 1, mid + 1, R, mid + 1, nR);
}

vector <query> q;
int N, t, a, b, k;

bool cmp(query q1, query q2){
    if(q1.idx == q2.idx) return q1.t < q2.t;
    return q1.idx < q2.idx;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    int cnt = 1;
    for(int i = 0; i < N; i++){
        cin >> t >> a >> b >> k;
        if(t == 1) q.push_back({t, a, b, k, cnt++, 0});
        else q.push_back({t, a, b, k, k, i});
        comp.push_back(a), comp.push_back(b), comp.push_back(a - 1);
    }
    sort(q.begin(), q.end(), cmp);
    for(int i = 0; i < N; i++){
        if(q[i].t == 2) q[i].idx = q[i].ans;
    }

    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int SZ = comp.size() - 1;
    for(int i = 0; i < N; i++){
        int L = lower_bound(comp.begin(), comp.end(), q[i].a) - comp.begin();
        int R = lower_bound(comp.begin(), comp.end(), q[i].b) - comp.begin();
        if(q[i].t == 1) K = q[i].k, Update(1, L, R, 1, SZ);
        else q[i].ans = Query(1, L, R, 1, SZ);
    }
    sort(q.begin(), q.end(), cmp);
    for(int i = 0; i < N; i++){
        if(q[i].t == 2) cout << q[i].ans << "\n";
    }
}
