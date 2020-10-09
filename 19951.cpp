#include <bits/stdc++.h>

using namespace std;

const int MX = 1e5 + 5;

int node[MX];
int N, M, A, B, H;

void Update(int i, int diff){
	while(i < MX){
		node[i] += diff;
		i += (i & -i);
	}
}

int Query(int i){
	int ret = 0;
	while(i){
		ret += node[i];
		i -= (i & -i);
	}
	return ret;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        cin >> H;
        if(i != N) Update(i + 1, -H);
        Update(i, H);
    }
    while(M--){
        cin >> A >> B >> H;
        if(B != N) Update(B + 1, -H);
        Update(A, H);
    }
    for(int i = 1; i <= N; i++) cout << Query(i) << " ";
}
