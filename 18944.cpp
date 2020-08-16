#include <bits/stdc++.h>

using namespace std;

const int MX = 5e5 + 5;

long long int score(int L, int R);

int N, T, A[MX], L, R;
vector <int> idx;
vector <int> v_pL, v_pR;
vector <long long int> sum;

int main(){
    scanf("%d %d", &N, &T);
    for(int i = 1; i <= N; i++) scanf("%d", &A[i]);
    long long int tmp = 1;
    idx.push_back(0), sum.push_back(0);
    for(int i = 1; i <= N; i++){
        if(A[i] <= A[i + 1]) tmp++;
        else sum.push_back(sum.back() + (tmp * (tmp + 1)) / 2), tmp = 1, idx.push_back(i);
    }
    v_pL.push_back(0), v_pR.push_back(0);
    tmp = 0;
    for(int i = 1; i <= N; i++){
        if(i > idx[tmp]) tmp++;
        v_pL.push_back(tmp);
    }
    tmp = 0;
    for(int i = 1; i <= N; i++){
        if(i == idx[tmp + 1]) tmp++;
        v_pR.push_back(tmp);
    }
    for(int i = 0; i < T; i++){
        scanf("%d %d", &L, &R);
        int lo = L, hi = R;
        while(lo < hi){
            int mid1 = (lo * 2 + hi) / 3, mid2 = (lo + hi * 2 + 2) / 3;
            long long int score1 = max(score(L, mid1), score(mid1, R));
            long long int score2 = max(score(L, mid2), score(mid2, R));
            if(score1 > score2) lo = mid1 + 1;
            else hi = mid2 - 1;
        }
        printf("%lld\n", max(score(L, lo), score(lo, R)));
    }
}

long long int score(int L, int R){
    int pL = v_pL[L];
    int pR = v_pR[R];
    long long int ret = sum[pR] - sum[pL];
    if(pL - 1 == pR){
        long long int gap = R - L + 1;
        ret = ((gap) * (gap + 1)) / 2;
    }
    else{
        long long int gap = idx[pL] - L + 1;
        ret += ((gap) * (gap + 1)) / 2;
        gap = R - idx[pR];
        ret += ((gap) * (gap + 1)) / 2;
    }
    return ret;
}
