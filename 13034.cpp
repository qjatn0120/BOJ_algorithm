#include <bits/stdc++.h>

using namespace std;

int N;
int cache[1005];
int grundy(int n){
    if(cache[n] != -1) return cache[n];
    bool chk[16] = {};
    for(int a = 0, b = n - 2; a <= b; a++, b--) chk[grundy(a) ^ grundy(b)] = true;
    int ret = 0;
    while(chk[ret]) ret++;
    return cache[n] = ret;
}

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    memset(cache, -1, sizeof(cache));
    cache[0] = cache[1] = 0;
    cin >> N;
    cout << (grundy(N) ? 1 : 2);
}
