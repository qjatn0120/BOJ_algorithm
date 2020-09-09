#include <bits/stdc++.h>

using namespace std;

const int MX = 5e5 + 5;

int N, M;
pair <long long int, long long int> money[MX], price[MX];

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 1; i <= N; i++) cin >> money[i].first >> money[i].second;
    for(int i = 1; i <= M; i++) cin >> price[i].first >> price[i].second;
    sort(money + 1, money + N + 1), sort(price + 1, price + M + 1);
    int p = 1, ans = 0;
    priority_queue <long long int> pq;
    for(int i = 1; i <= M; i++){
        while(p != N + 1 && money[p].first <= price[i].first) pq.push(-money[p++].second);
        while(!pq.empty() && -pq.top() < price[i].first) pq.pop();
        while(!pq.empty() && price[i].second) ans++, price[i].second--, pq.pop();
    }
    cout << ans;
}
