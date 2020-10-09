#include <bits/stdc++.h>

unsigned long long int N;

int main(){
    cin >> N;
    printf("%d",  __builtin_popcount(N) + __builtin_popcount(N >> 32));
}
