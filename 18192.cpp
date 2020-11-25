#include "bogoSort.h"
#include <bits/stdc++.h>

using namespace std;

void sort_array(int N)
{
    int tar = 0;
    while(1){
        vector <int> v = copy_array();
        while(tar < N && v[tar] == tar) tar++;
        if(tar == N) break;
        shuffle_array(tar, find(v.begin(), v.end(), tar) - v.begin());
    }
}
