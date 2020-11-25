#include <bits/stdc++.h>

using namespace std;

const int MX = 32005;

int Osum[MX], Esum[MX];

int N;
string s;
vector <pair<int, int> > ans;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> s;
    s = "X" + s;
    for(int i = 1; i <= N; i++){
        if(s[i] == 'H'){
            Osum[i] = Osum[i - 1] + 3;
            Esum[i] = Esum[i - 1] + 3;
        }else{
            if(i & 1){
                Osum[i] = Osum[i - 1] + 1;
                Esum[i] = Esum[i - 1] + 5;
            }else{
                Osum[i] = Osum[i - 1] + 5;
                Esum[i] = Esum[i - 1] + 1;
            }
        }
    }
    for(int x = 1; x <= Esum[N]; x++){
        int pos = 0, y = 0;
        while(pos < N){
            if(pos & 1) pos = lower_bound(Osum + pos, Osum + N + 1, x + Osum[pos]) - Osum;
            else pos = lower_bound(Esum + pos, Esum + N + 1, x + Esum[pos]) - Esum;
            y++;
        }
        if(pos == N) ans.push_back({x, y});
    }
    cout << ans.size() << "\n";
    for(auto i : ans) cout << i.first << " " << i.second << "\n";
}
