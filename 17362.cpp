#include <bits/stdc++.h>

using namespace std;

int n;

int main(){
    scanf("%d", &n), n--;
    int arr[8] = {1, 2, 3, 4, 5, 4, 3, 2};
    printf("%d", arr[n % 8]);
}
