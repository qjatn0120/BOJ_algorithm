#include <bits/stdc++.h>

using namespace std;

const int MX = 4005;
long long int ans;
int N, A[MX], B[MX], C[MX], D[MX];

int main(){
    cin >> N;
    for(int i = 0; i < N; i++) cin >> A[i] >> B[i] >> C[i] >> D[i];
    vector <int> v;
    for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++) v.push_back(A[i] + B[j]);
    sort(v.begin(), v.end());
    for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++){
        ans += upper_bound(v.begin(), v.end(), -C[i] - D[j]) - lower_bound(v.begin(), v.end(), -C[i] - D[j]);
    }
    cout << ans;

}
