#include <bits/stdc++.h>

using namespace std;

int N, A, g;
string str;
bool win;

int main(){
    scanf("%d", &N);
    while(N--) scanf("%d", &A), g ^= (A - 2);
    scanf("\n");
    getline(cin, str);
    win = str != "Whiteking";
    if(!g) win = !win;
    if(win) printf("Blackking");
    else printf("Whiteking");
}
