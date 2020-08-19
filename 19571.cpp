#include <bits/stdc++.h>

using namespace std;

int main(){
    int cnt = 1, arr[100][100];
    for(int j = 0; j < 100; j++){
        int i = j & 1 ? 0 : 99;
        for(int r = 0; r < 100; r++){
            arr[i][j] = i == j ? 9901 + j : cnt++;
            i = j & 1 ? i + 1 : i - 1;
        }
    }
    for(int j = 0; j < 100; j++){
        for(int i = 0; i < 100; i++) printf("%d ", arr[i][j]);
        printf("\n");
    }
}
