#include <bits/stdc++.h>

using namespace std;

int N, M;

int main(){
    scanf("%d %d", &N, &M);
    printf("%s", M < 3 ? "NEWBIE!" : M <= N ? "OLDBIE!" : "TLE!");
}
