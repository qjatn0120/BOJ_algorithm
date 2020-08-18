#include <bits/stdc++.h>

using namespace std;

struct{
    int weight;
    int cut;
    double piece;
}cake[55];


double gap();

int N, M;
double ans = INT_MAX;

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &cake[i].weight);
        cake[i].cut = 1;
        cake[i].piece = cake[i].weight;
    }
    scanf("%d", &M);
    ans = min(ans, gap());
    while(M--){
        double maxPiece = 0;
        int maxPos = 0;
        for(int i = 0; i < N; i++){
            if(maxPiece < cake[i].piece){
                maxPiece = cake[i].piece;
                maxPos = i;
            }
        }
        cake[maxPos].cut++;
        cake[maxPos].piece = (double)cake[maxPos].weight / cake[maxPos].cut;
        ans = min(ans, gap());
    }
    printf("%.11lf", ans);
}

double gap(){
    double MAX = 0, MIN = INT_MAX;
    for(int i = 0; i < N; i++){
        MAX = max(MAX, cake[i].piece);
        MIN = min(MIN, cake[i].piece);
    }
    return MAX - MIN;
}
