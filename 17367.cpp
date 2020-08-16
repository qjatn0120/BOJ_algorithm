#include <bits/stdc++.h>

using namespace std;

const int MX = 1005;

double calPrice(int a, int b, int c){
    if(a == b && b == c) return 10000 + a * 1000;
    if(a == b || a == c) return 1000 + a * 100;
    if(b == c) return 1000 + b * 100;
    return max(a, max(b, c)) * 100;
}

double cache[MX][220];

double DP(int a, int b){
    if(cache[a][b]) return cache[a][b];
    double price = calPrice(b / 36 + 1, (b / 6) % 6 + 1, b % 6 + 1);
    if(a == 0) return cache[a][b] = price;
    double ret = 0;
    for(int i = 0; i < 6; i++) ret += DP(a - 1, (b * 6) % 216 + i);
    ret /= 6;
    return cache[a][b] = max(ret, price);
}

int N;
double ans;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < 216; i++) ans += DP(N - 3, i);
    printf("%.10lf", ans / 216);
}
