#include <bits/stdc++.h>

using namespace std;

struct Square{
    long long int X1, Y1, X2, Y2;
    Square(long long int a, long long int b, long long int c){
        X1 = a - b - c;
        Y1 = a + b - c;
        X2 = a - b + c;
        Y2 = a + b + c;
    }
};

Square Merge(Square p, Square q){
    Square ret(0, 0, 0);
    ret.X1 = max(p.X1, q.X1);
    ret.X2 = min(p.X2, q.X2);
    ret.Y1 = max(p.Y1, q.Y1);
    ret.Y2 = min(p.Y2, q.Y2);
    return ret;
}

const int MX = 1e5 + 5;
int N;
long long int a[MX], b[MX], c[MX];

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
    bool able = true;
    for(int i = 1; i < N; i++) able &= ((a[0] + b[0] + c[0]) % 2 == (a[i] + b[i] + c[i]) % 2);
    if(!able){printf("NO"); return 0;}
    Square ans(a[0], b[0], c[0]);
    for(int i = 1; i < N; i++) ans = Merge(ans, Square(a[i], b[i], c[i]));
    if(ans.X1 <= ans.X2 && ans.Y1 <= ans.Y2) printf("%lld %lld", (ans.X1 + ans.Y1) / 2, (ans.Y1 - ans.X1) / 2);
    else printf("NO");
}
