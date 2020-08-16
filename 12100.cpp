#include <bits/stdc++.h>

using namespace std;

struct Board{
    int b[20][20];
};

void push(vector <int> &v);
int calc(int cnt, Board b);
void copy(Board to, Board from);

Board init;
int N;

int main(){
    scanf("%d", &N);
    for(int j = 0; j < N; j++)
    for(int i = 0; i < N; i++){
        scanf("%d", &init.b[i][j]);
    }
    printf("%d", calc(0, init));
}

void push(vector <int> &v){
    for(int i = 1; i < v.size(); i++){
        if(v[i - 1] == v[i]) v[i - 1] <<= 1, v[i] = 0;
    }
    int p = 0;
    for(int i = 0; i < v.size(); i++){
        swap(v[i], v[p]);
        if(v[p]) p++;
    }
    while(v.size() != N) v.push_back(0);
}

int calc(int cnt, Board b){
    int ret = 0;
    if(cnt == 5){
        for(int j = 0; j < N; j++)
        for(int i = 0; i < N; i++) ret = max(ret, b.b[i][j]);
        return ret;
    }
    Board next;
    vector <int> v;
    for(int i = 0; i < N; i++){
        v.clear();
        for(int j = 0; j < N; j++){
            if(b.b[i][j]) v.push_back(b.b[i][j]);
        }
        push(v);
        for(int j = 0; j < N; j++) next.b[i][j] = v[j];
    }
    ret = max(ret, calc(cnt + 1, next));
    for(int i = 0; i < N; i++){
        v.clear();
        for(int j = N - 1; j >= 0; j--){
            if(b.b[i][j]) v.push_back(b.b[i][j]);
        }
        push(v);
        for(int j = N - 1; j >= 0; j--) next.b[i][j] = v[j];
    }
    ret = max(ret, calc(cnt + 1, next));
    for(int j = 0; j < N; j++){
        v.clear();
        for(int i = 0; i < N; i++){
            if(b.b[i][j]) v.push_back(b.b[i][j]);
        }
        push(v);
        for(int i = 0; i < N; i++) next.b[i][j] = v[i];
    }
    ret = max(ret, calc(cnt + 1, next));
    for(int j = 0; j < N; j++){
        v.clear();
        for(int i = N - 1; i >= 0; i--){
            if(b.b[i][j]) v.push_back(b.b[i][j]);
        }
        push(v);
        for(int i = N - 1; i >= 0; i--) next.b[i][j] = v[i];
    }
    ret = max(ret, calc(cnt + 1, next));
    return ret;
}
