#include <bits/stdc++.h>

using namespace std;

const int MX = 105;

int R, C, arr[MX][MX], a;

void print(bool b){
    if(b){
        cout << "|>___/|        /}\n";
        cout << "| O < |       / }\n";
        cout << "(==0==)------/ }\n";
        cout << "| ^  _____    |\n";
        cout << "|_|_/     ||__|";
    }else{
        cout << "|>___/|     /}\n";
        cout << "| O O |    / }\n";
        cout << "( =0= )\"\"\"\"  \\\n";
        cout << "| ^  ____    |\n";
        cout << "|_|_/    ||__|";
    }
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> R >> C;
    for(int r = 1; r <= C; r++)
    for(int c = 1; c <= R; c++) cin >> arr[r][c];

    bool ans = true;
    for(int r = 1; r <= R; r++)
    for(int c = 1; c <= C; c++){
        cin >> a;
        if(arr[C - c + 1][r] != a) ans = false;
    }
    print(ans);

}
