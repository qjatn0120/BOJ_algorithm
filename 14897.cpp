#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

vector <int> node[MX * 4];
int N, Q, L, R, arr[MX], nxt[MX];

void MakeTree(int n, int L, int R){
    if(L == R){
        node[n].push_back(nxt[L]);
        return;
    }
    int mid = L + R >> 1;
    MakeTree(n * 2, L, mid), MakeTree(n * 2 + 1, mid + 1, R);
    auto p1 = node[n * 2].begin(), p2 = node[n * 2 + 1].begin();
    while(p1 != node[n * 2].end() || p2 != node[n * 2 + 1].end()){
        if(p1 == node[n * 2].end()) node[n].push_back(*p2), p2++;
        else if(p2 == node[n * 2 + 1].end()) node[n].push_back(*p1), p1++;
        else if((*p1) < (*p2)) node[n].push_back(*p1), p1++;
        else node[n].push_back(*p2), p2++;
    }
}

int Query(int n, int L, int R, int nL, int nR, int tar){
    if(L == nL && R == nR) return node[n].end() - upper_bound(node[n].begin(), node[n].end(), tar);
    int mid = nL + nR >> 1;
    if(R <= mid) return Query(n * 2, L, R, nL, mid, tar);
    if(L > mid) return Query(n * 2 + 1, L, R, mid + 1, nR, tar);
    else return Query(n * 2, L, mid, nL, mid, tar) + Query(n * 2 + 1, mid + 1, R, mid + 1, nR, tar);
}

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 0; i < N; i++) cin >> arr[i];
    map <int, int> mp;
    for(int i = 0; i < N; i++){
        auto ret = mp.insert({arr[i], i});
        if(!ret.second){
            nxt[ret.first->second] = i;
            ret.first->second = i;
        }
    }
    for(auto it : mp) nxt[it.second] = N;
    MakeTree(1, 0, N - 1);
    cin >> Q;
    for(int i = 0; i < Q; i++){
        cin >> L >> R;
        cout << Query(1, L - 1, R - 1, 0, N - 1, R - 1) << "\n";
    }
}
