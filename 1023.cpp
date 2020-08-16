#include <bits/stdc++.h>

using namespace std;

long long int pow2(int a){long long int tmp = 1; while(a--) tmp *= 2; return tmp;}
long long int DP(int a, int b);
void calc(int a, int b, long long int pos);
bool isAble();

long long int cache[55][55], K;
string ans = "";
int N;

int main(){
    scanf("%d %lld", &N, &K), K++;
    if(K > pow2(N) - DP(0, 0)){printf("-1"); return 0;}
    calc(0, 0, K);
    printf("%s", ans.c_str());
}

long long int DP(int a, int b){
    if(N % 2) return 0;
    if(a > N / 2 || b > N / 2) return 0;
    if(b > a) return 0;
    if(a == N / 2 && b == N / 2) return 1;
    if(cache[a][b]) return cache[a][b];
    return cache[a][b] = DP(a + 1, b) + DP(a, b + 1);
}

void calc(int a, int b, long long int pos){
    if(a + b == N) return;
    long long int cnt = pow2(N - a - b - 1);
    if(isAble()) cnt -= DP(a + 1, b);
    if(cnt >= pos) ans += "(", calc(a + 1, b, pos);
    else ans += ")", calc(a, b + 1, pos - cnt);
}

bool isAble(){
    int a = 0, b = 0;
    for(int i = 0; i < ans.size(); i++){
        if(ans[i] == '(') a++;
        else b++;
        if(b > a) return false;
    }
    return true;
}
