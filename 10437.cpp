#include <bits/stdc++.h>

using namespace std;

const int MX =  105;

priority_queue <pair<double, int> > pq;
pair <double, double> a, b, pos[MX];
double cost[MX];
int n;

double dist(pair <double, double> p, pair <double, double> q){return sqrt((p.first - q.first) * (p.first - q.first) + (p.second - q.second) * (p.second - q.second));}

int main(){
    scanf("%lf %lf", &a.first, &a.second);
    scanf("%lf %lf", &b.first, &b.second);
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%lf %lf", &pos[i].first, &pos[i].second);
    pos[0] = a, pos[n + 1] = b;
    for(int i = 1; i <= n + 1; i++){
        cost[i] = dist(pos[0], pos[i]) / 5;
        pq.push({-cost[i], i});
    }
    while(pq.size()){
        pair<double, int> tmp = pq.top();
        pq.pop();
        int nowPos = tmp.second;
        double nowCost = -tmp.first;
        if(nowCost != cost[nowPos]) continue;
        for(int nextPos = 1; nextPos <= n + 1; nextPos++){
            if(nextPos == nowPos) continue;
            double nextCost = min(dist(pos[nowPos], pos[nextPos]) / 5, 2 + abs(dist(pos[nowPos], pos[nextPos]) - 50) / 5) + nowCost;
            if(nextCost < cost[nextPos]){
                cost[nextPos] = nextCost;
                if(nextPos != n + 1) pq.push({-nextCost, nextPos});
            }
        }
    }
    printf("%.6lf", cost[n + 1]);
}
