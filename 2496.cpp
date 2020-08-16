#include <bits/stdc++.h>

using namespace std;

int N, M, T, K, A, B, ans, x, y;
vector <pair<int, int> > p;

void calc(int p1, int p2, int Lx);

int main(){
    scanf("%d %d %d %d", &N, &M, &T, &K);
    for(int i = 0; i < T; i++){
        scanf("%d %d", &A, &B);
        p.push_back({A + B, A - B});
    }
    sort(p.begin(), p.end());
    int p1 = 0, p2 = 0, Lx = p[0].first;
    while(1){
        while(p2 + 1 < p.size() && p[p2 + 1].first == Lx) p2++;
        while(Lx - p[p1].first > K) p1++;
        vector <int> v;
        for(int i = p1; i <= p2; i++) v.push_back(p[i].second);
        sort(v.begin(), v.end());
        int q1 = 0, q2 = 0;
        while(q2 < v.size()){
            while(p2 + 1 < v.size() && v[q2] == v[q2 + 1]) q2++;
            int Ly = v[q2];
            int midX = Lx - K / 2, midY = Ly - K / 2;
            if((midX + midY) & 1) midY++, Ly++;
            while(Ly - v[q1] > K) q1++;
            if(ans < q2 - q1 + 1){
                ans = q2 - q1 + 1;
                x = (midX + midY) / 2;
                y = (midX - midY) / 2;
            }
            q2++;
        }
        if(p[p2].first == Lx) Lx++;
        else{
            p2++;
            if(p2 == p.size()) break;
            Lx = p[p2].first;
        }
    }
    x = max(0, x), y = max(0, y);
    printf("%d %d\n%d", x, y, ans);
}
