#include <bits/stdc++.h>

using namespace std;

int N, M, arr[15][15];

set <int> st1, st2;

void f(vector <int> &v, set <int> &st){
    for(int i : v) st.insert(i);
    for(int sep = 1; sep < v.size(); sep++){
        vector <int> V;
        int p1 = sep - 1, p2 = sep;
        while(p1 >= 0 || p2 < v.size()){
            if(p1 < 0) V.push_back(v[p2]);
            else if(p2 >= v.size()) V.push_back(v[p1]);
            else V.push_back(v[p1] + v[p2]);
            p1--, p2++;
        }
        f(V, st);
    }
}

void calc(int n, set <int> &st){
    vector <int> v(n);
    for(int i = 0; i < n; i++) v[i] = (1 << i);
    f(v, st);
}

int sum(int a, int b){
    int ret = 0;
    for(int j = 0; j < N; j++)
    for(int i = 0; i < M; i++) if((a & (1 << i)) && (b & (1 << j))) ret += arr[i][j];
    return ret;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int j = 0; j < N; j++)
    for(int i = 0; i < M; i++) scanf("%d", &arr[i][j]);
    calc(M, st1), calc(N, st2);
    int ans = INT_MIN;
    for(auto it1 : st1)
    for(auto it2 : st2) ans = max(ans, sum(it1, it2));
    printf("%d", ans);
}
