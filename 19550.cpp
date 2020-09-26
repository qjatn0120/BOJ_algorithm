#include <bits/stdc++.h>

using namespace std;

const int MX = 1e4 + 5;

int N, L, s, e, s_table[20][MX];
bool is_loop[20][MX];
vector <pair<int, int> > v;

bool cmp(pair<int, int> p, pair<int, int> q){
    return p.second < q.second;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    //입력
    cin >> N >> L;
    for(int i = 0; i < N; i++){
        cin >> s >> e;
        if((s - e + L) % L < (e - s + L) % L) swap(s, e);
        v.push_back({s, e});
    }
    sort(v.begin(), v.end(), cmp);
    //좌표 압축
    map <int, int> mp;
    for(int i = 0; i < N; i++){
        mp.insert({v[i].first, 0});
        mp.insert({v[i].second, 0});
    }
    int cnt = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) it->second = cnt++;
    for(int i = 0; i < N; i++){
        v[i].first = mp[v[i].first];
        v[i].second = mp[v[i].second];
    }
    //fill sparse table [0]
    vector <pair<int, bool> > order[MX * 2];
    for(int i = 0; i < N; i++){
        order[v[i].first].push_back({i, true});
        order[v[i].second].push_back({i, false});
    }
    set <int> st;//segs not erased
    for(int i = 0; i < N; i++){
        if(v[i].first < v[i].second) st.insert(i);
    }

    for(int i = 0; i < cnt; i++){
        //시작점인 seg 제거
        for(auto t : order[i]){
            if(t.second) st.erase(t.first), st.erase(t.first + N);
        }

        //sparse table [0] update
        for(auto t : order[i]){
            if(!t.second){
                if(st.empty()) is_loop[0][t.first] = true, s_table[0][t.first] = t.first;
                else s_table[0][t.first] = (*st.begin()) % N;
            }
        }

        //끝점인 seg 추가
        for(auto t : order[i]){
            if(!t.second) st.insert(t.first + N);
        }
    }

    //fill sparse table [x]
    for(int j = 1; j < 20; j++){
        for(int i = 0; i < N; i++){
            int x = s_table[j - 1][i], y = s_table[j - 1][x];
            if(is_loop[j - 1][i] || is_loop[j - 1][x]) is_loop[j][i] = true;
            if((x - i + N) % N > (y - i + N) % N) is_loop[j][i] = true;cin.tie(NULL);
    ios::sync_with_stdio(false);
            s_table[j][i] = y;
        }
    }

    int ans = N;
    for(int i = 0; i < N; i++){
        int pos = i, num = 1;
        for(int j = 19; j >= 0; j--){
            if(is_loop[j][pos] || (pos - i + N) % N > (s_table[j][pos] - i + N) % N) continue;
            pos = s_table[j][pos];
            num += (1 << j);
        }
        ans = min(ans, num);
    }
    cout << ans;
}
