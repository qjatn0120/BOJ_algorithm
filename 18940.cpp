#include <bits/stdc++.h>

using namespace std;

const int MX = 205;

int grundy[MX], T, N;
bool cnt[MX];

int main(){
    grundy[0] = 0;
    grundy[1] = grundy[2] = 1;
    for(int i = 3; i < MX; i++){
        memset(cnt, 0, sizeof(cnt));
        cnt[grundy[i - 2]] = true;
        cnt[grundy[i - 3]] = true;
        for(int cut = 0; cut <= i - 3; cut++){
            int tmp = grundy[i - cut - 3] ^ grundy[cut];
            cnt[tmp] = true;
        }
        for(int j = 0; j < MX; j++){
            if(!cnt[j]){
                grundy[i] = j;
                break;
            }
        }
    }
    scanf("%d", &T);
    while(T--){
        scanf("%d", &N);
        if(N >= 100) N %= 34, N += 34 * 3;
        if(grundy[N]) printf("Yuto\n");
        else printf("Platina\n");
    }
}
