#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000;

struct mat{
    int N;
    vector <vector <int> > v;

    mat operator *(const mat &m){
        mat ret(N);
        for(int j = 0; j < N; j++)
        for(int i = 0; i < N; i++){
            for(int k = 0; k < N; k++)ret.v[j][i] += v[j][k] * m.v[k][i];
            ret.v[j][i] %= MOD;
        }
        return ret;
    }

    mat(int N) : N(N), v(N, vector <int>(N, 0)){}

    void print(){
        for(int j = 0; j < N; j++){
            for(int i = 0; i < N; i++) printf("%d ", v[j][i]);
            printf("\n");
        }
    }
};

int N, tmp;
long long int B;

mat pow(mat m, long long int b){
    if(b == 0){
        mat ret(N);
        for(int i = 0; i < N; i++) ret.v[i][i] = 1;
        return ret;
    }
    mat ret = pow(m, b >> 1);
    ret = ret * ret;
    if(b & 1) ret = ret * m;
    return ret;
}

int main(){
    scanf("%d %lld", &N, &B);
    mat init(N);
    for(int j = 0; j < N; j++)
    for(int i = 0; i < N; i++){
        scanf("%d", &tmp);
        init.v[j][i] = tmp;
    }
    mat ans = pow(init, B);
    ans.print();
}
