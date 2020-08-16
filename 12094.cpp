#include <bits/stdc++.h>

using namespace std;

const int MAX_MOVE = 10;

struct Board{
    int b[20][20];
};

vector <int> v(20);

void calc(int cnt, Board b);

Board init;
int N, MAX, ans;

int main(){
    scanf("%d", &N);
    for(int j = 0; j < N; j++)
    for(int i = 0; i < N; i++){
        scanf("%d", &init.b[i][j]);
        MAX += init.b[i][j];
    }
    for(int i = 1;;i <<= 1){
        if(i > MAX){
            MAX = i >> 1;
            break;
        }
    }
    calc(0, init);
    printf("%d", ans);
}

void push(){
    int p = 0;
    for(int i = 0; i < N; i++){
        swap(v[i], v[p]);
        if(v[p]) p++;
    }
    for(int i = 1; i < p; i++){
        if(v[i - 1] == v[i]) v[i - 1] <<= 1, v[i] = 0;
    }
    int q = 0;
    for(int i = 0; i < p; i++){
        swap(v[i], v[q]);
        if(v[q]) q++;
    }
}

void calc(int cnt, Board b){
    int maxBlock = 0;
    for(int j = 0; j < N; j++)
    for(int i = 0; i < N; i++) maxBlock = max(maxBlock, b.b[i][j]);
    ans = max(ans, maxBlock);
    int gap = ans / maxBlock;
    int left = 0;
    while(gap) gap >>= 1, left++;
    if(cnt + left > MAX_MOVE) return;
    if(ans == MAX) return;
    Board next;
    bool change;

    change = false;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) v[j] = b.b[i][j];
        push();
        for(int j = 0; j < N; j++) next.b[i][j] = v[j], change |= (b.b[i][j] != next.b[i][j]);
    }
    if(change) calc(cnt + 1, next);
    if(ans == MAX) return;

    change = false;
    for(int i = 0; i < N; i++){
        for(int j = N - 1; j >= 0; j--) v[N - 1 - j] = b.b[i][j];
        push();
        for(int j = N - 1; j >= 0; j--) next.b[i][j] = v[N - 1 - j], change |= (b.b[i][j] != next.b[i][j]);
    }
    if(change) calc(cnt + 1, next);
    if(ans == MAX) return;

    change = false;
    for(int j = 0; j < N; j++){
        for(int i = 0; i < N; i++) v[i] = b.b[i][j];
        push();
        for(int i = 0; i < N; i++) next.b[i][j] = v[i], change |= (b.b[i][j] != next.b[i][j]);
    }
    if(change) calc(cnt + 1, next);
    if(ans == MAX) return;

    change = false;
    for(int j = 0; j < N; j++){
        for(int i = N - 1; i >= 0; i--) v[N - 1 - i] = b.b[i][j];
        push();
        for(int i = N - 1; i >= 0; i--) next.b[i][j] = v[N - 1 - i], change |= (b.b[i][j] != next.b[i][j]);
    }
    if(change) calc(cnt + 1, next);
}
