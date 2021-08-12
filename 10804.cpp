#include <bits/stdc++.h>

using namespace std;

int arr[22], a, b;

int main(){
    iota(arr + 1, arr + 21, 1);

    for(int i = 0; i < 10; i++){
        cin >> a >> b;
        while(a < b) swap(arr[a], arr[b]), a++, b--;
    }

    for(int i = 1; i <= 20; i++) cout << arr[i] << " ";
}
