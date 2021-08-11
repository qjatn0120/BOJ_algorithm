#include <bits/stdc++.h>

using namespace std;

int calc(int x, int y);

int T, a, b;

int main(){
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &a, &b);
        int ans = calc(a, b);
        if(ans) printf("%d\n", ans);
        else printf("10\n");
    }
}

int calc(int a, int b){
    if(b == 0) return 1;
    int tmp = calc(a, b / 2);
    if(b % 2) return (tmp * tmp * a) % 10;
    else return (tmp * tmp) % 10;
}
