#include <bits/stdc++.h>

using namespace std;

const long long int MAX = 1e18 + 5;

string M, S;
long long int k, Q;
long long int a, b;

int main(){
    cin.tie(NULL), ios::sync_with_stdio(false);
    getline(cin, M);
    getline(cin, S);
    cin >> k >> Q;
    long long int cnt = 0;
    for(char c : S) cnt += c == '$';
    if(cnt == 1){
        int pos;
        for(pos = 0; S[pos] != '$'; pos++);
        string S1 = S.substr(0, pos), S2 = S.substr(pos + 1, S.size());
        for(int i = 0; i < Q; i++){
            cin >> a >> b;
            a--, b--;
            for(long long int j = a; j <= b; j++){
                long long int p = j;
                if(p < S1.size() * k) cout << S1[p % S1.size()];
                else{
                    p -= S1.size() * k;
                    if(p < M.size()) cout << M[p];
                    else{
                        p -= M.size();
                        cout << S2[p % S2.size()];
                    }
                }
            }
            cout << "\n";
        }
    }else{
        int pos;
        long long int k_;
        vector <long long int> len;
        vector <long long int> cntSum[66];
        len.push_back(M.size());
        for(k_ = 1; k_ < k; k_++){
            long long int next_len = len.back() * cnt;
            if(next_len / len.back() != cnt || next_len % len.back() ||next_len + (S.size() - cnt) > MAX) break;
            len.push_back(next_len + (S.size() - cnt));
        }
        for(int i = 0; i < (int)M.size(); i++) cntSum[0].push_back(i);
        for(int i = 1; i <= k_; i++){
            cntSum[i].push_back(0);
            for(int j = 1; j < (int)S.size(); j++){
                long long int tmp = cntSum[i].back() + (S[j - 1] == '$' ? len[i - 1] : 1);
                if(tmp >= MAX) tmp = MAX;
                cntSum[i].push_back(tmp);
            }
        }
        for(pos = 0; S[pos]!= '$'; pos++);
        string S1 = S.substr(0, pos);
        for(int i = 0; i < Q; i++){
            cin >> a >> b;
            a--, b--;
            long long int kpos = k_;
            if(b < (long long int)S1.size() * (k - kpos)){
                for(long long int j = a; j <= b; j++) cout << S1[j % S1.size()];
                cout << "\n";
                continue;
            }
            if(a < (long long int)S1.size() * (k - kpos)){
                while(a < (long long int)S1.size() * (k - kpos)) cout << S1[a % (long long int)S1.size()], a++;
            }
            a -= S1.size() * (k - kpos), b -= S1.size() * (k - kpos);
            b -= a;
            long long int p[66] = {};
            while(a){
                p[kpos] = upper_bound(cntSum[kpos].begin(), cntSum[kpos].end(), a) - cntSum[kpos].begin();
                p[kpos]--;
                a -= cntSum[kpos][p[kpos]];
                if(kpos && S[p[kpos]] == '$') kpos--;
            }
            while(kpos && S[p[kpos]] == '$') kpos--;
            b++;
            while(b--){
                cout << (kpos ? S[p[kpos]] : M[p[kpos]]);
                if(b == 0) break;
                p[kpos]++;
                while(p[kpos] == (kpos ? S.size() : M.size())) kpos++, p[kpos]++;
                while(kpos && S[p[kpos]] == '$') kpos--, p[kpos] = 0;
            }
            cout << "\n";
        }
    }
}
