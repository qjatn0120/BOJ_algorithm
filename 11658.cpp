#include <bits/stdc++.h>

using namespace std;

const int MX = 1030;

struct FenwickTree{

    int node[MX];

    void Update(int n, int diff){
        while(n < MX){
            node[n] += diff;
            n += (n & -n);
        }
    }

    int Query(int n){
        int ret = 0;
        while(n){
            ret += node[n];
            n -= (n & -n);
        }
        return ret;
    }

};

struct FenwickTree2D{

    FenwickTree tree[MX];

    void Update(int x, int y, int diff){
        while(x < MX){
            tree[x].Update(y, diff);
            x += (x & -x);
        }
    }

    int Query(int x, int y){
        int ret = 0;
        while(x){
            ret += tree[x].Query(y);
            x -= (x & -x);
        }
        return ret;
    }

}tree2D;

int N, M, w, X1, Y1, X2, Y2, c, arr[MX][MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int x = 1; x <= N; x++)
    for(int y = 1; y <= N; y++){
        cin >> arr[x][y];
        tree2D.Update(x, y, arr[x][y]);
    }

    while(M--){
        cin >> w;
        if(w == 0){
            cin >> X1 >> Y1 >> c;
            int diff = c - arr[X1][Y1];
            arr[X1][Y1] = c;
            tree2D.Update(X1, Y1, diff);
        }else{
            cin >> X1 >> Y1 >> X2 >> Y2;
            cout << (tree2D.Query(X2, Y2) - tree2D.Query(X1 - 1, Y2) - tree2D.Query(X2, Y1 - 1) + tree2D.Query(X1 - 1, Y1 - 1)) << "\n";
        }
    }
}
