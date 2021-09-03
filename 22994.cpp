#include <bits/stdc++.h>

using namespace std;

int n, m;
string s[1005];

bool test1(int gap){
    for(int r = 0; r < n; r++){
        char tar;
        for(int c = 0; c < m; c++){
            if(c % gap == 0) tar = s[r][c];
            else if(tar != s[r][c]) return false;
        }
    }
    return true;
}

bool test2(int gap){
    for(int c = 0; c < m; c++){
        char tar;
        for(int r = 0; r < n; r++){
            if(r % gap == 0) tar = s[r][c];
            else if(tar != s[r][c]) return false;
        }
    }
    return true;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> s[i];

    int comp1, comp2;

    for(int i = 1; i <= m; i++){
        if(m % i == 0 && test1(i)) comp1 = i;
    }

    for(int i = 1; i <= n; i++){
        if(n % i == 0 && test2(i)) comp2 = i;
    }

    cout << (n / comp2) << " " << (m / comp1) << "\n";

    for(int r = 0; r < n; r += comp2){
        for(int c = 0; c < m; c += comp1) cout << s[r][c];
        cout << "\n";
    }
}
