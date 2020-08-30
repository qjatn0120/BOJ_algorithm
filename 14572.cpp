#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

struct student{
    int d;
    vector <int> v;
}stu[MX];

bool cmp(student a, student b){return a.d < b.d;}

int cnt[35], ans, N, K, D, M, A;

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    cin >> N >> K >> D;
    for(int i = 0; i < N; i++){
        cin >> M >> stu[i].d;
        while(M--) cin >> A, stu[i].v.push_back(A);
    }
    sort(stu, stu + N, cmp);
    int p1 = 0;
    for(int p2 = 0; p2 < N; p2++){
        for(int i : stu[p2].v) cnt[i]++;
        while(stu[p2].d - stu[p1].d > D){
            for(int i : stu[p1].v) cnt[i]--;
            p1++;
        }
        int tmp = 0;
        for(int i = 1; i <= K; i++) tmp += (cnt[i] && cnt[i] != p2 - p1 + 1);
        ans = max(ans, tmp * (p2 - p1 + 1));
    }
    cout << ans;
}
