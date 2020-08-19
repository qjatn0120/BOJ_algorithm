#include <bits/stdc++.h>

using namespace std;

const int MX = 1e6 + 5;

int n;
long long int x[MX], sum[MX], DP[MX], a, b, c;
 //DP[i] = min or max a(i)b(j) + c(j) + d(i) for j = 1 ~ i - 1

long long int A(int i){return -2 * a * sum[i];}
long long int B(int j){return sum[j];}
long long int C(int j){return DP[j] + a * sum[j] * sum[j] - b * sum[j];}
long long int D(int i){return a * sum[i] * sum[i] + b * sum[i] + c;}

double cross(pair<long long int, long long int> a, pair<long long int, long long int> b){
    return (double)(a.second - b.second) / (b.first - a.first);
}

void getDP(){
    vector <pair<long long int, long long int> > Line;
    vector <double> crossP;
    DP[1] = a * x[1] * x[1] + b * x[1] + c;
    for(int i = 2; i <= n; i++){
        pair<long long int, long long int> tLine = {B(i - 1), C(i - 1)};
        while(!crossP.empty() && crossP.back() >= cross(Line.back(), tLine)) crossP.pop_back(), Line.pop_back();
        if(!Line.empty()) crossP.push_back(cross(Line.back(), tLine));
        Line.push_back(tLine);
        int pos = lower_bound(crossP.begin(), crossP.end(), A(i)) - crossP.begin();
        DP[i] = A(i) * Line[pos].first + Line[pos].second + D(i);
        DP[i] = max(DP[i], a * sum[i] * sum[i] + b * sum[i] + c);
    }
}

int main(){
    scanf("%d%lld %lld %lld", &n, &a, &b, &c);
    for(int i = 1; i <= n; i++) scanf("%lld", &x[i]), sum[i] = sum[i - 1] + x[i];
    getDP();
    printf("%lld", DP[n]);
}
