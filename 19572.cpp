#include <bits/stdc++.h>

using namespace std;

void print(int n){
    printf("%d", n / 2);
    if(n & 1) printf(".5");
    else printf(".0");
    printf(" ");
}

int d1, d2, d3, a, b, c;

int main(){
    scanf("%d %d %d", &d1, &d2, &d3);
    a = d1 + d2 - d3;
    b = d1 + d3 - d2;
    c = d2 + d3 - d1;
    if(a <= 0 || b <= 0 || c <= 0) printf("-1");
    else{
        printf("1\n");
        print(a), print(b), print(c);
    }
}
