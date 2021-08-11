#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;

int N, arr[MX], cnt, ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
        if(arr[i - 1] == arr[i]) i--, N--;
    }
    arr[N + 1] = 0;


    for(int i = 1; i <= N; i++){
        if(arr[i] > arr[i - 1] && arr[i] > arr[i + 1]){
            if(!(i == N && cnt == 0)) cnt++;
        }
    }

    while(cnt){
        if(cnt == 1) cnt = 0;
        else cnt = (cnt + 1) / 2;
        ans++;
    }
    cout << ans;
}
