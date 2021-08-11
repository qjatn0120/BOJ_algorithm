#include <bits/stdc++.h>

const double err = 0.000001;

int T;
int x[2], y[2], r[2];

int main(){
    scanf("%d", &T);
    while(T--){
        for(int i = 0; i < 2; i++) scanf("%d %d %d", &x[i], &y[i], &r[i]);
        double dis = (x[1] - x[0]) * (x[1] - x[0]) + (y[1] - y[0]) * (y[1] - y[0]);
        dis = sqrt(dis);
        if(x[0] == x[1] && y[0] == y[1] && r[0] == r[1]) printf("-1\n");
        else if(dis < abs(r[1] - r[0]) - err) printf("0\n");
        else if(dis > r[0] + r[1] + err) printf("0\n");
        else if(r[0] + r[1] - err < dis && dis < r[0] + r[1] + err) printf("1\n");
        else if(abs(r[0] - r[1]) - err < dis && dis < abs(r[0] - r[1]) + err) printf("1\n");
        else printf("2\n");
    }
}
