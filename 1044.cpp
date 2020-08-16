#include <bits/stdc++.h>

using namespace std;

long long int ABS(long long int a){return a > 0 ? a : -a;}
int bitNum(int a);
long long int calScore1(int bit);
long long int calScore2(int bit);

int N;
long long int A[40], B[40], ans, minGap = LONG_LONG_MAX;
map <long long int, int> mp1[20];
map <long long int, int, greater<long long int> > mp2[20];

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%lld", &A[i]);
    for(int i = 0; i < N; i++) scanf("%lld", &B[i]);
    for(int i = 0; i < (1 << N / 2); i++){
        long long int sum = calScore1(i);
        int bNum = bitNum(i);
        if(mp1[bNum].find(sum) == mp1[bNum].end()) mp1[bNum][sum] = i;
    }
    for(int i = 0; i < (1 << N / 2); i++){
        long long int sum = calScore2(i);
        int bNum = bitNum(i);
        if(mp2[bNum].find(sum) == mp2[bNum].end()) mp2[bNum][sum] = i;
    }
    for(int K = 0; K <= N / 2; K++){
        map<long long int, int>::iterator it1 = mp1[K].begin();
        map<long long int, int, greater<long long int> >::iterator it2 = mp2[N / 2 - K].begin();
        while(it1 != mp1[K].end() && it2 != mp2[N / 2 - K].end()){
            long long int gap = ABS(it1->first + it2->first);
            if(gap < minGap){
                minGap = gap;
                ans = it1->second * (1LL << N / 2) + it2->second;
            }else if(gap == minGap){
                ans = min(ans, it1->second * (1LL << N / 2) + it2->second);
            }
            if(it1->first + it2->first < 0) it1++;
            else it2++;
        }
    }
    for(int i = N - 1; i >= 0; i--){
        if(ans & (1LL << i)) printf("2 ");
        else printf("1 ");
    }
}

int bitNum(int a){
    int re = 0;
    while(a) a -= (a & -a), re++;
    return re;
}

long long int calScore1(int bit){
    long long int sum = 0;
    for(int i = 0; i < N / 2; i++){
        if(bit & (1 << (N / 2 - 1 - i))) sum -= B[i];
        else sum += A[i];
    }
    return sum;
}

long long int calScore2(int bit){
    long long int sum = 0;
    for(int i = 0; i < N / 2; i++){
        if(bit & (1 << (N / 2 - 1 - i))) sum -= B[i + N / 2];
        else sum += A[i + N / 2];
    }
    return sum;
}
