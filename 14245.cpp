#include <bits/stdc++.h>

using namespace std;

const int MX = (1 << 19) + 1;

int node[MX];

void Update(int n, int diff){
    while(n < MX){
        node[n] ^= diff;
        n += (n & -n);
    }
}

int Query(int n){
    int ret = 0;
    while(n){
        ret ^= node[n];
        n -= (n & -n);
    }
    return ret;
}

int n, m, t, a, b, c;

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> n;
    int bef = 0;
    for(int i = 1; i <= n; i++){
        cin >> a;
        Update(i, a ^ bef);
        bef = a;
    }
    cin >> m;
    for(int i = 0; i < m; i++){
        cin >> t;
        if(t == 2){
            cin >> a;
            a++;
            cout << Query(a) << "\n";
        }else{
            cin >> a >> b >> c;
            a++, b++;
            Update(a, c);
            if(b != n) Update(b + 1, c);
        }
    }
}
