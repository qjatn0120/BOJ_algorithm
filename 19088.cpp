#include <bits/stdc++.h>

using namespace std;

const long long int MOD = 1e9 + 7;
const int MX = (1e5 + 5) * 2;

vector <int> idx;
set <int> Set;
vector <pair<int, int> > query;
int N, Q, D, x, y;
long long int A[MX], w[MX], DPOW[MX];

struct Node{
    int num, L, R, leaf;
    long long int val;
};

struct SegmentTree{

    Node node[MX * 3];

    void makeTree(int n, int L, int R){
        node[n].L = L, node[n].R = R, node[n].val = node[n].num = 0;
        if(L == R) return;
        int mid = (L + R) >> 1;
        makeTree(n * 2, L, mid);
        makeTree(n * 2 + 1, mid + 1, R);
    }

    void addCard(int n, int tar){
        if(node[n].L == node[n].R){
            node[n].num++;
            node[n].val = (DPOW[node[n].num] * idx[node[n].L]) % MOD;
            return;
        }
        if(tar <= node[n * 2].R) addCard(n * 2, tar);
        else addCard(n * 2 + 1, tar);
        node[n].num = node[n * 2].num + node[n * 2 + 1].num;
        node[n].val = (node[n * 2].val + node[n * 2 + 1].val * w[node[n * 2].num]) % MOD;
    }

    void deleteCard(int n, int tar){
        if(node[n].L == node[n].R){
            node[n].num--;
            node[n].val = (DPOW[node[n].num] * idx[node[n].L]) % MOD;
            return;
        }
        if(tar <= node[n * 2].R) deleteCard(n * 2, tar);
        else deleteCard(n * 2 + 1, tar);
        node[n].num = node[n * 2].num + node[n * 2 + 1].num;
        node[n].val = (node[n * 2].val + node[n * 2 + 1].val * w[node[n * 2].num]) % MOD;
    }

}ST;

int main(){
    scanf("%d %d %d", &N, &Q, &D);
    w[0] = 1;
    for(int i = 1; i < MX; i++) w[i] = (w[i - 1] * D) % MOD;
    DPOW[0] = 0;
    for(int i = 1; i < MX; i++) DPOW[i] = (w[i - 1] + DPOW[i - 1]) % MOD;
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
        if(Set.find(A[i]) == Set.end()) Set.insert(A[i]);
    }
    for(int i = 0; i < Q; i++){
        scanf("%d %d", &x, &y);
        if(Set.find(y) == Set.end()) Set.insert(y);
        query.push_back({x - 1, y});
    }
    for(auto it = Set.begin(); it != Set.end(); it++) idx.push_back(*it);
    for(int i = 0; i < N; i++) A[i] = lower_bound(idx.begin(), idx.end(), A[i]) - idx.begin();
    for(int i = 0; i < Q; i++) query[i].second = lower_bound(idx.begin(), idx.end(), query[i].second) - idx.begin();
    ST.makeTree(1, 0, idx.size() - 1);
    for(int i = 0; i < N; i++) ST.addCard(1, A[i]);
    printf("%lld\n", ST.node[1].val);
    for(int i = 0; i < Q; i++){
        ST.deleteCard(1, A[query[i].first]);
        ST.addCard(1, query[i].second);
        A[query[i].first] = query[i].second;
        printf("%lld\n", ST.node[1].val);
    }
}
