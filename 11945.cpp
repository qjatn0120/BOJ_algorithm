#include <bits/stdc++.h>

using namespace std;

int n, ans = 1;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < 32; i++){
        if(n & (1 << i)) ans = i + 1;
    }
    printf("%d", ans);
}
