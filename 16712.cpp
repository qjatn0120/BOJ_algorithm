#include <bits/stdc++.h>

using namespace std;

const int MX = 505;

int N, M, a[MX], V;
vector <int> v;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> a[i];
    for(int i = 0; i < N; i++){
        v.push_back(a[i]);
        if(v.size() == M){
            cin >> V;
            sort(v.begin(), v.end());
            v.erase(v.begin() + V - 1);
        }
    }
    for(int i : v) cout << i << "\n";
}
