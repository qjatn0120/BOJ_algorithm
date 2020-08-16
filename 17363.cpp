#include <bits/stdc++.h>

using namespace std;

int N, M;
char arr[105][105];

int main(){
    scanf("%d %d\n", &N, &M);
    for(int i = 0; i < N; i++){
        for(int j = M - 1; j >= 0; j--){
            scanf("%c", &arr[i][j]);
        }
        scanf("\n");
    }
    for(int j = 0; j < M; j++){
        for(int i = 0; i < N; i++){
            if(arr[i][j] == '-') arr[i][j] = '|';
            else if(arr[i][j] == '|') arr[i][j] = '-';
            else if(arr[i][j] == '/') arr[i][j] = '\\';
            else if(arr[i][j] == '\\') arr[i][j] = '/';
            else if(arr[i][j] == '^') arr[i][j] = '<';
            else if(arr[i][j] == '<') arr[i][j] = 'v';
            else if(arr[i][j] == 'v') arr[i][j] = '>';
            else if(arr[i][j] == '>') arr[i][j] = '^';
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}
