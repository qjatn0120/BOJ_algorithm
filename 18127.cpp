#include <bits/stdc++.h>

using namespace std;

const int MX = 5005;

long long int A, B;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> A >> B;
    A -= 2;
    cout << (B + 1 + A * ((B * (B + 1) / 2)));
}
