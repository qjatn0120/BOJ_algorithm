#include <bits/stdc++.h>

using  namespace std;

int N, h, A, B, sum;

int main(){
    scanf("%d", &N);
    while(N--){
        scanf("%d", &h);
        A += (h & 1);
        B += (h >> 1);
        sum += h;
    }
    printf("%s", A <= B && sum % 3 == 0 ? "YES" : "NO");
}
