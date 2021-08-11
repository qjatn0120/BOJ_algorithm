#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

struct FenwickTree{
    vector <int> v;

    FenwickTree(int sz) : v(sz) {}

    void Update(int n, int c){
        while(n < (int)v.size()){
            v[n] += c;
            n += (n & -n);
        }
    }

    int Query(int n){
        int ret = 0;
        while(n){
            ret += v[n];
            n -= (n & -n);
        }
        return ret;
    }
};

int tree[MX * 4], lazy[MX * 4];

void prop(int n, bool isLeaf){
    tree[n] += lazy[n];
    if(!isLeaf){
        lazy[n * 2] += lazy[n];
        lazy[n * 2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void Update(int n, int l, int r, int nL, int nR, int c){
    if(lazy[n]) prop(n, nL == nR);
    if(r < nL || l > nR) return;

    if(l <= nL && nR <= r){
        lazy[n] += c;
        prop(n, nL == nR);
        return;
    }

    int mid = (nL + nR) >> 1;
    Update(n * 2, l, r, nL, mid, c);
    Update(n * 2 + 1, l, r, mid + 1, nR, c);

    tree[n] = min(tree[n * 2], tree[n * 2 + 1]);
}

int N, a[MX];
int inv[MX]; // number of inversions
long long int ans[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);

    cin >> N;
    for(int i = 0; i < N; i++) cin >> a[i];

    vector <int> v;
    for(int i = 0; i < N; i++) v.push_back(a[i]);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int i = 0; i < N; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    int M = (int)v.size();

    FenwickTree bit1(M + 1), bit2(M + 1);
    for(int i = 0; i < N; i++){
        bit2.Update(a[i] + 1, 1);
        bit2.Update(M + 1, -1);
    }

    long long int sum = 0;
    for(int i = 0; i < N; i++){
        inv[i] = bit1.Query(a[i]) + bit2.Query(a[i]);
        sum += inv[i];
        bit1.Update(1, 1);
        bit1.Update(a[i], -1);
        bit2.Update(a[i] + 1, -1);
        bit2.Update(M + 1, 1);
    }
    sum /= 2;

    for(int i = 0; i < N; i++) Update(1, a[i] + 1, M + 1, 0, M + 1, 1);
    for(int i = 0; i < N; i++){
        Update(1, a[i] + 1, M + 1, 0, M + 1, -1);
        ans[i] = sum - (inv[i] - tree[1]);
        Update(1, 0, a[i] - 1, 0, M + 1, 1);
    }

    for(int i = 0; i < N; i++) cout << ans[i] << " ";
}
