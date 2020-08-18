#include <bits/stdc++.h>

using namespace std;

const double PI = 3.14159265358979323846;

struct FastFourierTransform{

    vector <complex<double> > w;

    void FillW(complex <double> a, int n){
        complex <double> tmp = 1;
        for(int i = 0; i < n; i++) w.push_back(tmp), tmp *= a;
    }

    complex <double> wPow(int a){
        if(a < 0) a += w.size();
        return w[a];
    }

    void DFT(vector<complex<double> > &f, int n){
        int N = f.size();
        if(N == 1) return;
        vector<complex<double> > f_odd, f_even;
        for(int i = 0; i < N; i++){
            if(i % 2) f_odd.push_back(f[i]);
            else f_even.push_back(f[i]);
        }
        DFT(f_odd, n * 2);
        DFT(f_even, n * 2);
        for(int i = 0; i < N; i++){
            f[i] = f_even[i % (N / 2)] + f_odd[i % (N / 2)] * wPow(i * n);
        }
    }

}FFT;

int N, tmp, bef_N;
long long int ans = 0;

int main(){
    scanf("%d", &N), bef_N = N;
    vector <complex<double> > A, B, C;
    for(int i = 0; i < N; i++) scanf("%d", &tmp), A.push_back(tmp);
    for(int i = 0; i < N; i++) scanf("%d", &tmp), B.push_back(tmp);
    reverse(B.begin(), B.end());
    int tmp = 1;
    while(tmp < N) tmp *= 2;
    while(N != tmp) N++, A.push_back(0), B.push_back(0);
    for(int i = 0; i < N; i++) A.push_back(0), B.push_back(0);

    FFT.FillW(complex <double> (cos(PI / N), sin(PI / N)), 2 * N);
    FFT.DFT(A, 1), FFT.DFT(B, 1);
    for(int i = 0; i < 2 * N; i++) C.push_back(A[i] * B[i]);
    FFT.DFT(C, -1);
    vector <long long int> result;
    for(int i = 0; i < 2 * N; i++) result.push_back((long long int)(real(C[i]) / (2 * N) + 0.01));
    for(int i = 0; i < bef_N; i++) ans = max(ans, result[i] + result[i + bef_N]);
    printf("%lld", ans);
}
