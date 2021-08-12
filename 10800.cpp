#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;

vector <int> v, color[MX];
vector <long long int> sum, colorsum[MX];
int N, C[MX], S[MX];

void getSum(vector <int> &v1, vector <long long int> &v2){
    if(v1.empty()) return;
    v2.push_back(v1[0]);
    for(int i = 1; i < (int)v1.size(); i++){
        v2.push_back(v2.back() + v1[i]);
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> C[i] >> S[i];
        v.push_back(S[i]);
        color[C[i]].push_back(S[i]);
    }

    sort(v.begin(), v.end());
    for(int i = 1; i <= N; i++) sort(color[i].begin(), color[i].end());

    getSum(v, sum);
    for(int i = 1; i <= N; i++) getSum(color[i], colorsum[i]);

    for(int i = 0; i < N; i++){
        long long int ans = 0;
        int it = lower_bound(v.begin(), v.end(), S[i]) - v.begin() - 1;
        if(it != -1) ans = sum[it];
        it = lower_bound(color[C[i]].begin(), color[C[i]].end(), S[i]) - color[C[i]].begin() - 1;
        if(it != -1) ans -= colorsum[C[i]][it];
        cout << ans << "\n";
    }
}
