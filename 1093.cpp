#include <bits/stdc++.h>

using namespace std;

const int MX = 40;

int N, K, tmp, init;
int val[MX], price[MX];

map <int, int> mp1, mp2;

void makeMap(int s, map <int, int> &mp){
    for(int i = 0; i < (1 << 16); i++){
        int sum1 = 0, sum2 = 0;
        for(int j = 0; j < 16; j++){
            if(i & (1 << j)) sum1 += val[j + s], sum2 += price[j + s];
        }
        auto ret = mp.insert({sum1, sum2});
        if(!ret.second) ret.first->second = min(ret.first->second, sum2);
    }
}

void uniqueMap(map <int, int> &mp){
    auto it = mp.begin();
    while(1){
        auto bef = it++;
        if(it == mp.end()) return;
        if(bef->second >= it->second){
            mp.erase(bef);
            if(it != mp.begin()) it--;
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &price[i]);
    for(int i = 0; i < N; i++) scanf("%d", &val[i]);
    scanf("%d", &K);
    scanf("%d", &N);
    for(int i = 0; i < N; i++) scanf("%d", &tmp), init += price[tmp];
    makeMap(0, mp1), makeMap(16, mp2);
    uniqueMap(mp1), uniqueMap(mp2);
    int ans = 1e9;
    auto it1 = mp1.begin(), it2 = --mp2.end();
    while(1){
        int valSum = it1->first + it2->first;
        int priceSum = it1->second + it2->second;
        if(valSum >= K){
            ans = min(ans, priceSum);
            if(it2 == mp2.begin()) break;
            it2--;
        }else{
            it1++;
            if(it1 == mp1.end()) break;
        }
    }
    printf("%d", ans < 1e9 ? max(ans - init, 0) : -1);
}
