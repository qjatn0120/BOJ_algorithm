#include <bits/stdc++.h>

using namespace std;

string s;
char c;
int K;

int main(){
    cin >> s, c = 'a';
    for(char ch : s){
        if(c == 'a') K++;
        while(c != ch){
            c = c == 'z' ? 'a' : c + 1;
            if(c == 'a') K++;
        }
        c = c == 'z' ? 'a' : c + 1;
    }
    printf("%d", K);
}
