#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

struct Node{
    int val, l, r;
};

int N, Q, L, R, ans, arr[MX], nxt[MX], idx[MX];

vector <Node> node;
vector <int> comp, root;
map <int, int> mp;

void make_init_tree(int n, int L, int R){
    node.push_back({0, -1, -1});
    if(L == R) return;
    int mid = L + R >> 1;
    node[n].l = node.size();
    make_init_tree(node[n].l, L, mid);
    node[n].r = node.size();
    make_init_tree(node[n].r, mid + 1, R);
}

int tar;
void make_Kth_tree(int n, int pos, int L, int R){
    node.push_back({0, -1, -1});
    if(L == R){
        node[pos].val = 1;
        return;
    }
    int mid = L + R >> 1;
    if(tar <= mid){
        node[pos].r = node[n].r;
        node[pos].l = node.size();
        make_Kth_tree(node[n].l , node.size(), L, mid);
    }else{
        node[pos].l = node[n].l;
        node[pos].r = node.size();
        make_Kth_tree(node[n].r, node.size(), mid + 1, R);
    }
    node[pos].val = node[node[pos].l].val + node[node[pos].r].val;
}

int Query(int n, int L, int R, int nL, int nR){
    if(L == nL && R == nR) return node[n].val;
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(node[n].l, L, R, nL, mid);
    else if(L > mid) return Query(node[n].r, L, R, mid + 1, nR);
    else return Query(node[n].l, L, mid, nL, mid) + Query(node[n].r, mid + 1, R, mid + 1, nR);
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> arr[i], comp.push_back(arr[i]);
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for(int i = 1; i <= N; i++) arr[i] = lower_bound(comp.begin(), comp.end(), arr[i]) - comp.begin() + 1;
    for(int i = 1; i <= N; i++){
        auto ret = mp.insert({arr[i], i});
        if(!ret.second){
            nxt[ret.first->second] = i;
            ret.first->second = i;
        }
    }
    root.push_back(0);
    make_init_tree(0, 1, N);
    for(int i = 1; i <= N; i++) idx[nxt[i]] = i;
    for(int i = 1; i <= N; i++){
        if(idx[i]){
            int tmp = root.back();
            root.push_back(node.size());
            tar = idx[i];
            make_Kth_tree(tmp, node.size(), 1, N);
        }else root.push_back(root.back());
    }
    cin >> Q;
    while(Q--){
        cin >> L >> R;
        L += ans;
        ans = (R - L + 1) - Query(root[R], L, R, 1, N);
        cout << ans << "\n";
    }
}
