#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int main(){
    scanf("%d %d %d", &a, &b, &c);
    int d = abs(a) + abs(b);
    if(d <= c && (d - c) % 2 == 0) printf("YES");
    else printf("NO");
}
