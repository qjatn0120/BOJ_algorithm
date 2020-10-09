#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

unsigned reverse_bit(unsigned n, unsigned k){
    unsigned r = 0;
    for(int i = 0; i < k; i++) r |= ((n >> i) & 1) << (k - i - 1);
    return r;
}

void fft(vector <complex<double> > &v, bool is_reverse){
    unsigned n = v.size(), k = __builtin_ctz(n);
    for(unsigned i = 0; i < n; i++){
        unsigned j = reverse_bit(i, k);
        if(i < j) swap(v[i], v[j]);
    }
    for(int s = 2; s <= n; s <<= 1){
        double t = 2 * PI / s * (is_reverse ? -1 : 1);
        complex <double> ws(cos(t), sin(t));
        for(int i = 0; i < n; i += s){
            complex <double> w(1);
            for(int j = 0; j < s / 2; j++){
                complex <double> tmp = v[i + j + s / 2] * w;
                v[i + j + s / 2] = v[i + j] - tmp;
                v[i + j] += tmp;
                w *= ws;
            }
        }
    }
    if(is_reverse){
        for(int i = 0; i < n; i++) v[i] /= n;
    }
}

vector <complex<double> > A, B;
string s1, s2;

int cut = 2;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> s1 >> s2;
    for(int i = s1.size() - 1; i >= 0; i -= cut){
        A.push_back(0);
        int w = 1;
        for(int j = 0; j < cut; j++){
            if(i - j >= 0) A[A.size() - 1] += (s1[i - j] - '0') * w;
            w *= 10;
        }
    }
    for(int i = s2.size() - 1; i >= 0; i -= cut){
        B.push_back(0);
        int w = 1;
        for(int j = 0; j < cut; j++){
            if(i - j >= 0) B[B.size() - 1] += (s2[i - j] - '0') * w;
            w *= 10;
        }
    }
    int n = max(A.size(), B.size()), np = 1;
    while(np < n * 2) np <<= 1;
    while(A.size() < np) A.push_back(0);
    while(B.size() < np) B.push_back(0);
    fft(A, false);
    fft(B, false);
    for(int i = 0; i < np; i++) A[i] *= B[i];
    fft(A, true);
    vector <int> ans;
    for(int i = 0; i < A.size(); i++) ans.push_back(A[i].real() + 0.5);
    int w = 1;
    for(int i = 0; i < cut; i++) w *= 10;
    for(int i = 0; i < ans.size() - 1; i++) ans[i + 1] += ans[i] / w, ans[i] %= w;
    bool b = false;
    for(int i = ans.size() - 1; i >= 0; i--){
        if(b) cout << setfill('0') << setw(cut) << ans[i];
        else{
            if(ans[i]){
                cout << ans[i];
                b = true;
            }
        }
    }
    if(!b) cout << 0;
}
