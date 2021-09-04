#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

int N, Q, M, v, arr[MX], bef[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> Q;
    for(int i = 1; i <= N; i++) cin >> arr[i];
    cin >> M;
    cout << N << " " << Q << "\n";
    while(M--){
        cin >> v;
        cout << "2 " << v << "\n";
        Q--;
    }

    int root;
    for(int i = 1; i <= N; i++){
        if(arr[i] != i) bef[arr[i]]++;
        else root = i;
    }
    queue <int> q;
    for(int i = 1; i <= N; i++){
        if(!bef[i]) q.push(i);
    }

    while(!q.empty()){
        int pos = q.front();
        q.pop();
        if(arr[pos] == pos) continue;
        cout << "1 " << pos << " " << arr[pos] << "\n";
        bef[arr[pos]]--;
        if(!bef[arr[pos]]) q.push(arr[pos]);
        Q--;
    }

    while(Q--){
        cout << "1 " << root << " " << root << "\n";
    }

}
