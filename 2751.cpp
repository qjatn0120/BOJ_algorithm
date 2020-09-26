#include <bits/stdc++.h>

using namespace std;

vector <int> v;
int n;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int tmp;
        scanf("%d", &tmp);
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n; i++)
        printf("%d\n", v[i]);
}
