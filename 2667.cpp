#include <bits/stdc++.h>

using namespace std;

const int dir_x[4] = {1, 0, -1, 0}, dir_y[4] = {0, 1, 0, -1};

int N, arr[30][30];
string s;
vector <int> v;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    for(int j = 1; j <= N; j++){
        cin >> s;
        for(int i = 1; i <= N; i++) arr[j][i] = s[i - 1] - '0';
    }
    for(int j = 1; j <= N; j++)
    for(int i = 1; i <= N; i++){
        if(arr[j][i] == 1){
            int cnt = 1;
            queue <pair<int, int> > q;
            q.push({i, j});
            arr[j][i] = 0;
            while(!q.empty()){
                auto pos = q.front();
                q.pop();
                for(int dir = 0; dir < 4; dir++){
                    int px = pos.first + dir_x[dir], py = pos.second + dir_y[dir];
                    if(arr[py][px] == 1){
                        q.push({px, py});
                        arr[py][px] = 0;
                        cnt++;
                    }
                }
            }
            v.push_back(cnt);
        }
    }
    sort(v.begin(), v.end());
    cout << v.size() << "\n";
    for(int i : v) cout << i << "\n";
}
