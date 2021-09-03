#include <bits/stdc++.h>

using namespace std;

int N, A;
long long int player;
priority_queue <int, vector <int>, greater <int> > pq;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> player; N--;
    while(N--) cin >> A, pq.push(A);
    while(!pq.empty()){
        if(pq.top() >= player) break;
        player += pq.top();
        pq.pop();
    }
    cout << (pq.empty() ? "Yes" : "No");
}
