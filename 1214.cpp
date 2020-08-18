#include <bits/stdc++.h>

using namespace std;

int D, P, Q, ans;

int main(){
    scanf("%d %d %d", &D, &P, &Q);
    if(P < Q) swap(P, Q);
    ans = P * ((D - 1) / P + 1);
    for(int i = 0; i < Q; i++){
        if(P * i >= D) break;
        ans = min(ans,  ((D - P * i - 1) / Q + 1) * Q + P * i);
    }
    printf("%d", ans);
}
