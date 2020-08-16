#include <bits/stdc++.h>

using namespace std;

int N;
string str;

int calc(string s, vector <bool> v);

int main(){
    scanf("%d\n", &N);
    getline(cin, str);
    vector <bool> b;
    for(int i = 0; i < (N << 1); i++) b.push_back(false);
    printf("%d", calc(str, b));
}

int calc(string s, vector <bool> v){
    if(s.size() == 1){
        if(s[0] == '1') return 0;
        else if(s[0] == '0'){
            int ret = 1;
            for(int i = 0; i < N; i++) if(!v[i * 2]) ret = ret << 1;
            return ret;
        }else{
            int tar = s[0] - 'a';
            if(v[tar << 1] & v[(tar << 1) + 1]) return 0;
            v[tar << 1] = true, s[0] = '0';
            return calc(s, v);
        }
    }
    if(s.size() == 4) s += string("?1:0");
    if(s[3] == '0' || s[3] == '1') swap(s[0], s[3]);
    int tar1 = s[0] - 'a', tar2 = s[3] - 'a';
    int cut = 5, cnt1 = 1, cnt2 = 0;
    while(cnt1 != cnt2){
        if(s[cut] == '?') cnt1++;
        if(s[cut] == ':') cnt2++;
        if(cnt1 == cnt2) break;
        cut++;
    }
    string s1 = s.substr(5, cut - 5);
    string s2 = s.substr(cut + 1, s.size());
    if(tar1 == tar2) return calc(s1, v);
    if(s[3] == '0' || s[3] == '1') return calc(s2, v);
    int ret = 0;
    if(s[0] == '0'){
        if(!(v[tar2 << 1] & v[(tar2 << 1) + 1])){
            vector <bool> newV(v);
            newV[tar2 << 1] = true;
            ret += calc(s1, newV);
        }
        if(!(v[tar2 << 1] & !v[(tar2 << 1) + 1])){
            vector <bool> newV(v);
            newV[tar2 << 1] = newV[(tar2 << 1) + 1] = true;
            ret += calc(s2, newV);
        }
    }else if(s[0] == '1'){
        if(!(v[tar2 << 1] & v[(tar2 << 1) + 1])){
            vector <bool> newV(v);
            newV[tar2 << 1] = true;
            ret += calc(s2, newV);
        }
        if(!(v[tar2 << 1] & !v[(tar2 << 1) + 1])){
            vector <bool> newV(v);
            newV[tar2 << 1] = newV[(tar2 << 1) + 1] = true;
            ret += calc(s1, newV);
        }

    }else{
        if(!(v[tar1 << 1] & v[(tar1 << 1) + 1]) && !(v[tar2 << 1] & v[(tar2 << 1) + 1])){//tar1==0, tar2==0
            vector <bool> newV(v);
            newV[tar1 << 1] = newV[tar2 << 1] = true;
            ret += calc(s1, newV);
        }
        if(!(v[tar1 << 1] & v[(tar1 << 1) + 1]) && !(v[tar2 << 1] & !v[(tar2 << 1) + 1])){//tar1 == 0, tar2 == 1
            vector <bool> newV(v);
            newV[tar1 << 1] = newV[tar2 << 1] = newV[(tar2 << 1) + 1] = true;
            ret += calc(s2, newV);
        }
        if(!(v[tar1 << 1] & !v[(tar1 << 1) + 1]) && !(v[tar2 << 1] & v[(tar2 << 1) + 1])){//tar1 == 1, tar2 == 0
            vector <bool> newV(v);
            newV[tar1 << 1] = newV[tar2 << 1] = newV[(tar1 << 1) + 1] = true;
            ret += calc(s2, newV);
        }
        if(!(v[tar1 << 1] & !v[(tar1 << 1) + 1]) && !(v[tar2 << 1] & !v[(tar2 << 1) + 1])){//tar1 == 1, tar2 == 1
            vector <bool> newV(v);
            newV[tar1 << 1] = newV[tar2 << 1] = newV[(tar1 << 1) + 1] = newV[(tar2 << 1) + 1] = true;
            ret += calc(s1, newV);
        }
    }

    return ret;
}
