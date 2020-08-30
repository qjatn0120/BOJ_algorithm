#include <bits/stdc++.h>

using namespace std;

vector <int> v;

void getPrime(const int MAX){
    bool b[MAX] = {};
    fill(b, b + MAX, true);
    for(int i = 2; i < MAX; i++){
        if(!b[i]) continue;
        v.push_back(i);
        for(int j = i * 2; j < MAX; j += i) b[j] = false;
    }
}

long long int POW(int a, int b){
    if(b == 0) return 1;
    long long int ret = POW(a, b / 2);
    ret *= ret;
    if(b & 1) ret *= a;
    return ret;
}

long long int eulerPhi(int n){
    long long int ret = 1;
    for(int Div : v){
        int cnt = 0;
        while(n % Div == 0) cnt++, n /= Div;
        if(cnt) ret *= pow(Div, cnt - 1) * (Div - 1);
        if(n == 1) break;
    }
    if(n != 1) ret *= (n - 1);
    return ret;
}

int N;

int main(){
    getPrime((int)sqrt(1e9) + 1);
    scanf("%d", &N);
    for(int i = 1; i <= 69300; i++){
        if(N % i == 0 && i * eulerPhi(i) == N){
            printf("%d", i);
            return 0;
        }
    }
    printf("-1");
}
