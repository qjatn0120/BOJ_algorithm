#include <bits/stdc++.h>

using namespace std;

typedef struct INFO{
    pair<int, int> p;
    string name;
}Info;

bool cmp(Info a, Info b){if(a.p.first < b.p.first) return true; if(a.p.first == b.p.first && a.p.second < b.p.second) return true; return false;}

int N;
vector <Info> v;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        Info tmp;
        scanf("%d ", &tmp.p.first);
        tmp.p.second = i;
        getline(cin, tmp.name);
        v.push_back(tmp);
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < N; i++){
        printf("%d %s\n", v[i].p.first, v[i].name.c_str());
    }
}
