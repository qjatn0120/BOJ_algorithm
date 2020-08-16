#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

vector <int> group[MX];

int N, M, k, a;
bool aff[MX], init[MX];

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d", &k);
        while(k--) scanf("%d", &a), group[i].push_back(a);
    }
    for(int i = 1; i <= N; i++){
        scanf("%d", &a);
        aff[i] = init[i] = a;
    }
    for(int i = M - 1; i >= 0; i--){
        bool isAff = true;
        for(int tar : group[i]) isAff &= aff[tar];
        if(!isAff) for(int tar : group[i]) aff[tar] = false;
    }
    bool ans[MX];
    for(int i = 1; i <= N; i++) ans[i] = aff[i];
    for(int i = 0; i < M; i++){
        bool isAff = false;
        for(int tar : group[i]) isAff |= aff[tar];
        if(isAff) for(int tar : group[i]) aff[tar] = true;
    }
    bool isAns = true;
    for(int i = 1; i <= N; i++){
        if(aff[i] != init[i]) isAns = false;
    }
    if(isAns){
        printf("YES\n");
        for(int i = 1; i <= N; i++) printf("%d ", (int)ans[i]);
    }else printf("NO");
}
