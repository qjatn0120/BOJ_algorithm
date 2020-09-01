#include <bits/stdc++.h>

using namespace std;

int N, M, K;
vector <int> v[26];
string s;

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++){
        cin >> s;
        v[i].push_back(0);
        for(int j = 0; j < s.size(); j++){
            if(s[j] == 'U') v[i].push_back(j + 1);
        }
    }
    cin >> s;
    reverse(s.begin(), s.end());
    int p1, p2 = M, st = s[0] - 'A';
    p1 = v[st].back() == M ? v[st][v[st].size() - 2] : v[st].back();
    p1++;
    long long int ans = p2 - p1 + 1;
    for(int i = 1; i < s.size(); i++){
        if(p1 > p2) break;
        st = s[i] - 'A';
        auto it = lower_bound(v[st].begin(), v[st].end(), p1);
        it--;
        p1 = (*it) + 1;
        it = upper_bound(v[st].begin(), v[st].end(), p2);
        it--;
        p2 = *it;
        ans += p2 - p1 + 1;
    }
    cout << ans;
}
