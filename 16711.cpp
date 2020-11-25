#include <bits/stdc++.h>

using namespace std;

const int MX = 505;

struct Order{
    int r1, c1, r2, c2;
    long long int k;
};

int N, M;
long long int arr[MX][MX], odd, even;
vector <Order> ans;

void Move(int r1, int c1, int r2, int c2){
    ans.push_back({r2, c2, r1, c2, arr[r1][c1]});
    ans.push_back({r1, c1, r1, c2, -arr[r1][c1]});
    arr[r2][c2] += arr[r1][c1];
    arr[r1][c1] = 0;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 1; i <= N; i++)
    for(int j = 1; j <= M; j++){
        cin >> arr[i][j];
        if((i +j) & 1) odd += arr[i][j];
        else even += arr[i][j];
    }
    if(odd - even){cout << -1; return 0;}
    for(int i = N; i > 2; i--){
        Move(i, 1, i - 1, 2);
        for(int j = 2; j <= M; j++) Move(i, j, i - 1, j - 1);
    }
    for(int j = M; j > 1; j--){
        Move(1, j, 2, j - 1);
        Move(2, j, 1, j - 1);
    }
    ans.push_back({1, 1, 2, 1, -arr[1][1]});
    cout << ans.size() << "\n";
    for(Order tmp : ans){
        cout << tmp.r1 << " " << tmp.c1 << " " <<  tmp.r2 << " " << tmp.c2 << " " << tmp.k << "\n";
    }
}
