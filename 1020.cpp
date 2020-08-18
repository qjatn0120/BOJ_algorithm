#include <bits/stdc++.h>

using namespace std;

int num[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
int arr[8] = {0, 0, 1, 7, 4, 2, 0, 8};
long long int DP[20][120];//i자리로 j를 만드는 가장 작은 수
const long long int inf = 1e17;
long long int MX = 1;
int N, tar = 0;

long long int pow10(int a){long long int tmp = 1; while(a--) tmp *= 10; return tmp;}
long long int fillDP(int a, int b);
long long int calc(long long int a);

int main(){
    string str;
    cin >> str;
    N = str.size();
    for(int i = 0; i < N; i++) MX *= 10;
    long long int n = 0, tmp;
    for(int i = 0; i < N; i++) n *= 10, n += str[i] - '0';
    tmp = n;
    for(int i = 0; i < N; i++) tar += num[tmp % 10], tmp /= 10;
    long long int ans = calc(n + 1);
    if(ans < inf) printf("%lld\n", ans - n);
    else printf("%lld\n", MX + calc(0) - n);
}

long long int fillDP(int a, int b){
    if(a == 1){
        for(int i = 2; i <= 7; i++)
            if(i == b) return arr[i];
        return inf;
    }
    if(b < 2) return inf;
    if(DP[a][b]) return DP[a][b];
    long long int re = inf;
    for(int i = 2; i <= 7; i++)
        re = min(re, fillDP(a - 1, b - i) * 10 + arr[i]);
    return DP[a][b] = re;
}

long long int calc(long long int a){
    if(a == 0){
        if(N * 6 == tar) return a;
        return calc(a + 1);
    }
    if(a >= MX) return inf;
    if(a % 10 != 0){
        long long int tmp = a;
        int cnt = 0;
        for(int i = 0; i < N; i++) cnt += num[tmp % 10], tmp /= 10;
        if(cnt == tar) return a;
        else return calc(a + 1);
    }else{
        int cnt = 0, n0 = 0;
        while(a % 10 == 0) a /= 10, n0++;
        long long int tmp = a;
        for(int i = 0; i < N - n0; i++) cnt += num[tmp % 10], tmp /= 10;
        long long int re = a * pow10(n0) + fillDP(n0, tar - cnt);
        if(re < inf) return re;
        return calc((a + 1) * pow10(n0));
    }
}
