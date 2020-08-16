#include <bits/stdc++.h>

using namespace std;

const int MX = 3e5 + 5;
int len, N;
bool b[MX][2];

int main(){
    scanf("%d", &N);
    N -= 6;
    if(N % 10 == 0){
        len = 5;
        b[4][0] = true;
    }else if(N % 10 == 1){
        len = 5;
        b[4][0] = b[3][0] = true;
    }else if(N % 10 == 2){
        len = 6;
        b[5][0] = b[3][0] = true;
    }else if(N % 10 == 3){
        len = 7;
        b[6][0] = b[2][0] = true;
    }else if(N % 10 == 4){
        len = 7;
        b[6][0] = b[5][0] = b[2][0] = true;
    }else  if(N % 10 == 5){
        len = 8;
        b[7][0] = b[5][0] = b[2][0] = true;
    }else if(N % 10 == 6){
        len = 8;
        b[7][0] = b[6][0] = b[4][0] = b[2][0] = true;
    }else if(N % 10 == 7){
        len = 9;
        b[8][0] = b[6][0] = b[4][0] = b[2][0] = true;
    }else if(N % 10 == 8){
        len = 10;
        b[9][0] = b[8][0] = b[7][0] = b[8][1] = true;
    }else if(N % 10 == 9){
        len = 10;
        b[9][0] = b[8][0] = b[7][0] = b[6][0] = b[8][1] = true;
    }
    N /= 10;
    while(N--){
        b[len + 5][0] = b[len + 5][1] = b[len + 6][0] = true;
        len += 7;
    }
    for(int i = 1; i < len; i++) printf("%d %d\n", i, i + 1);
    int cnt = len + 1;
    for(int i = 2; i < len; i++) if(b[i][0]) printf("%d %d\n", i, cnt++);
    for(int i = 2; i < len; i++) if(b[i][1]) printf("%d %d\n", i, cnt++);
}
