#include <bits/stdc++.h>

using namespace std;

int a, b, c, d, e, f;

int main(){
    scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    printf("%d %d\n", (c * e - b * f) / (a * e - b * d), (c * d - a * f) / (b * d - a * e));
}
