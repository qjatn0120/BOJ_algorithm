#include <bits/stdc++.h>

using namespace std;

const int MX = 11;
int DP[MX], Y;

int main(){
    scanf("%d %d", &DP[0], &Y);
    for(int i = 1; i <= Y; i++){
        DP[i] = DP[i - 1] * 105 / 100;
        if(i >= 3) DP[i] = max(DP[i], DP[i - 3] * 120 / 100);
        if(i >= 5) DP[i] = max(DP[i], DP[i - 5] * 135 / 100);
    }
    printf("%d", DP[Y]);
}
