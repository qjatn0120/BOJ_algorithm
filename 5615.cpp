#include <bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

/**
test n is prime for unsigned int n
**/

/*
if n < 2,047, it is enough to test a = 2
if n < 1,373,653, it is enough to test a = 2 and 3
if n < 9,080,191, it is enough to test a = 31 and 73
if n < 25,326,001, it is enough to test a = 2, 3, and 5
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61
*/

const int MAX_PRIME = 1000000;

bool isPrime[MAX_PRIME + 5];
vector <ull> pList = {2, 7, 61};

ull pow(ull x, ull y, ull mod){
    x %= mod;
    ull ret = 1;
    while(y){
        if(y & 1) ret = (ret * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return ret;
}

bool miller_rabin(ull n, ull a){
    ull k = n - 1;
    while(!(k & 1)){
        if(pow(a, k, n) == n - 1) return true;
        k >>= 1;
    }
    ull tmp = pow(a, k, n);
    return tmp == n - 1 || tmp == 1;
}

bool is_prime(ull n) {
    if(n <= MAX_PRIME) return isPrime[n];
    for(ull a : pList){
        if(!miller_rabin(n, a)) return false;
    }
    return true;
}

void getPrime(int n){
    memset(isPrime, -1, sizeof(isPrime));
    for(int i = 2; i * i <= n; i++){
        if(isPrime[i]){
            for(int j = i * i; j <= n; j += i) isPrime[j] = false;
        }
    }
}

int N, ans;
ull A;

int main(){
    getPrime(MAX_PRIME);
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N;
    while(N--){
        cin >> A;
        A = (A << 1) + 1;
        if(is_prime(A)) ans++;
    }
    cout << ans;
}
