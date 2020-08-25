#include <bits/stdc++.h>

using namespace std;

const int MX = 5005;

int N, a[MX], bef[MX], cnt[MX];

vector <int> adj[MX];

int main(){
    scanf("%d", &N);
    fill(cnt, cnt + N, 1);
    for(int i = 0; i < N; i++) scanf("%d", &a[i]);
    sort(a, a + N);
    for(int i = 0; i < N; i++)
    for(int j = i + 1; j < N; j++){
        if(a[j] % a[i] == 0) adj[i].push_back(j), bef[j]++;
    }
    queue <int> q;
    for(int i = 0; i < N; i++) if(!bef[i]) q.push(i);
    while(!q.empty()){
        int pos = q.front();
        q.pop();
        for(int next : adj[pos]){
            cnt[next] = max(cnt[next], cnt[pos] + 1);
            bef[next]--;
            if(!bef[next]) q.push(next);
        }
    }
    printf("%d", N - *max_element(cnt, cnt + N));
}
