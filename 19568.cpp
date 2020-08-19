#include <bits/stdc++.h>

using namespace std;

int main(){
    for(int j = 0; j < 30; j++){
    for(int i = 0; i < 30; i++){
        if(i == 15 && j > 15) printf("1 ");
        else if(i == 15 && j < 15) printf("15 ");
        else if(i < 15 && j == 15) printf("225 ");
        else if(i > 15 && j == 15) printf("3375 ");
        else printf("0 ");
    }
        printf("\n");
    }
}
