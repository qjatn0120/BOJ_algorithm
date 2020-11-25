#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

vector <int> adj[MX];
int N, M, K, C[MX], S, E;
bitset <500001> b1, b2;

void BFS(queue <int> &q, bitset <500001> &b){
    for(int i = 0; i < 2; i++){
        int sz = q.size();
        while(sz--){
            int pos = q.front();
            q.pop();
            for(int next : adj[pos]){
                if(b.test(next)) continue;
                q.push(next), b.set(next);
            }
        }
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++) cin >> C[i];
    for(int i = 0; i < M; i++){
        cin >> S >> E;
         adj[S].push_back(E);
         adj[E].push_back(S);
    }
    if(!K){cout << C[1]; return 0;}
    int lo = 0, hi = 1e9;
    while(lo < hi){
        int mid = lo + hi >> 1;
        queue <int> q1, q2;
        b1.reset(), b2.reset();
        q1.push(1), b1.set(1);
        for(int i = 1; i <= N; i++) if(C[i] <= mid) q2.push(i), b2.set(i);
        BFS(q1, b1), BFS(q2, b2);
        b2.flip();
        if((b1 & b2).any()) lo = mid + 1;
        else hi = mid;
    }
    cout << lo;
}
