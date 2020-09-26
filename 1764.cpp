#include <bits/stdc++.h>

using namespace std;

int N, M;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    string s;
    set <string> st;
    vector <string> v;
    for(int i = 0; i < N; i++){
        cin >> s;
        st.insert(s);
    }
    for(int i = 0; i < M; i++){
        cin >> s;
        if(st.find(s) != st.end()) v.push_back(s);
    }
    sort(v.begin(), v.end());
    cout << v.size() << "\n";
    for(string i : v) cout << i << "\n";
}
