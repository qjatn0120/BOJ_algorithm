#include <bits/stdc++.h>

using namespace std;

const int MX = 4587520 * 4;

int MAX[MX], MIN[MX], lazy[MX];

void prop(int n){
    MAX[n] += lazy[n], MIN[n] += lazy[n];
    if(n * 2 + 1 < MX) lazy[n * 2] += lazy[n], lazy[n * 2 + 1] += lazy[n];
    lazy[n] = 0;
}

void update(int n, int L, int R, int nL, int nR, int diff){
    if(L == nL && R == nR){
        lazy[n] += diff;
        prop(n);
        return;
    }
    if(lazy[n]) prop(n);
    int mid = nL + nR >> 1;
    if(R <= mid) update(n * 2, L, R, nL, mid, diff), prop(n * 2 + 1);
    else if(L > mid) update(n * 2 + 1, L, R, mid + 1, nR, diff), prop(n * 2);
    else update(n * 2, L, mid, nL, mid, diff), update(n * 2 + 1, mid + 1, R, mid + 1, nR, diff);
    if(nL != nR){
        MAX[n] = max(MAX[n * 2], MAX[n * 2 + 1]);
        MIN[n] = min(MIN[n * 2], MIN[n * 2 + 1]);
    }
}

int query(bool b, int n, int L, int R, int nL, int nR){
    if(lazy[n]) prop(n);
    if(L == nL && R == nR) return b ? MAX[n] : MIN[n];
    int mid = nL + nR >> 1;
    if(R <= mid) return query(b, n * 2, L, R, nL, mid);
    else if(L > mid) return query(b, n * 2 + 1, L ,R, mid + 1, nR);
    else{
        int q1 = query(b, n * 2, L, mid, nL, mid);
        int q2 = query(b, n * 2 + 1, mid + 1, R, mid + 1, nR);
        return b ? max(q1, q2) : min(q1, q2);
    }
}

string str;
int C, N, O, a, b, c;

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> C >> N >> O;
    for(int i = 0; i < O; i++){
        cin >> str;
        if(str.compare("state") == 0){
            cin >> a, a++;
            cout << query(false, 1, a, a, 1, C) << "\n";
        }else{
            if(str.compare("change") == 0){
                cin >> b >> c, b++;
                a = b;
            }else{
                cin >> a >> b >> c, a++, b++;
            }
            if(c > 0){
                int MAX = query(true, 1, a, b, 1, C);
                c = min(c, N - MAX);
            }else{
                int MIN = query(false, 1, a, b, 1, C);
                c = max(c, -MIN);
            }
            update(1, a, b, 1, C, c);
            cout << c << "\n";
        }
    }
}
