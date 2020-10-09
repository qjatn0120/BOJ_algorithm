#include <bits/stdc++.h>

/*
if n < 2,047, it is enough to test a = 2
if n < 1,373,653, it is enough to test a = 2 and 3
if n < 9,080,191, it is enough to test a = 31 and 73
if n < 25,326,001, it is enough to test a = 2, 3, and 5
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61
if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
if n < 18,446,744,073,709,551,616 = 264, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
*/

using namespace std;
const long long int MAX_PRIME = 1000000;

bool isPrime[MAX_PRIME + 5];
vector <long long int> pList = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

long long int gcd(long long int a, long long int b){
    long long int tmp;
    while(b){
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// (p * q) % mod without overflow
long long int mult(long long int p,long long int q, long long int mod){
    p %= mod, q %= mod;
    long long int ret = 0;
    while(q){
        if(q & 1) ret = (ret + p) % mod;
        p = (p + p) % mod;
        q >>= 1;
    }
    return ret;
}

//p^q % mod without overflow
long long int pow(long long int p, long long int q, long long int mod){
    p %= mod;
    long long int ret = 1;
    while(q){
        if(q & 1) ret = mult(ret, p, mod);
        p = mult(p, p, mod);
        q >>= 1;
    }
     return ret;
}

bool miller_rabin(long long int n, long long int a){
    long long int k = n - 1;
    while(!(k & 1)){
        if(pow(a, k, n) == n - 1) return true;
        k >>= 1;
    }
    long long int tmp = pow(a, k, n);
    return tmp == n - 1 || tmp == 1;
}

bool is_prime(long long int n) {
    if(n <= MAX_PRIME) return isPrime[n];

    for(long long int a : pList){
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

long long int Pollard_Rho(long long int n){
    long long int x = rand() % (n - 2) + 2;
    long long int y = x;
    long long int c = rand() % (n - 1) + 1;
    while(1){
        x = (mult(x, x, n) + c) % n;
        y = (mult(y, y, n) + c) % n;
        y = (mult(y, y, n) + c) % n;
        long long int d = gcd(abs(y - x), n);
        if(d == 1) continue;
        if(is_prime(d)) return d;
        else return Pollard_Rho(d);
    }
}

void getFactor(long long int n, vector <long long int> &v){
    while(!(n & 1)){
        n >>= 1;
        v.push_back(2);
    }
    while(n != 1 && !is_prime(n)){
        long long int d = Pollard_Rho(n);
        while(n % d == 0){
            n /= d;
            v.push_back(d);
        }
    }
    if(n != 1) v.push_back(n);
    sort(v.begin(), v.end());
}

long long int N;
vector <long long int> ans;

int main(){
    srand((unsigned)time(NULL));
    getPrime(MAX_PRIME);
    scanf("%lld", &N);
    getFactor(N, ans);
    for(long long int i : ans) printf("%lld\n", i);
}
