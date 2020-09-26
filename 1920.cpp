#include <bits/stdc++.h>

using namespace std;
//1 4 5 6 8
//0 5
//6
int n, m, tmp;
vector <int> v;

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &tmp), v.push_back(tmp);
    sort(v.begin(), v.end());
    scanf("%d", &m);
    for(int i = 0; i < m; i++){
        scanf("%d", &tmp);
        int lo = 0, hi = n;
        bool b = false;
        while(lo <= hi){
            int mid = (lo + hi) / 2;
            if(v[mid] < tmp) lo = mid + 1;
            else if(v[mid] > tmp) hi = mid - 1;
            else{
                b = true;
                break;
            }
        }
        printf("%d\n", b);
    }
}
