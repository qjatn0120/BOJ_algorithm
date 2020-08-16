#include <bits/stdc++.h>

using namespace std;

const int MX = 2e5 + 5;
const long long int MOD = 1e9 + 7;

struct Node{
    int n;
    char c;
    int next[26];

    Node(char c) : n(0), c(c){
        for(int i = 0; i < 26; i++) next[i] = -1;
    }
};

int N;
string tmp;
char tar[MX];
long long int DP[MX];
long long int w[MX][305];
long long int w_size[MX];
vector <Node> node;

void addString(string str){
    int pos = 0;
    for(int i = 0; i < str.size(); i++){
        int to = str[i] - 'a';
        node[pos].n++;
        if(node[pos].next[to] == -1){
            node[pos].next[to] = node.size();
            node.push_back(Node(str[i]));
        }
        pos = node[pos].next[to];
    }
    node[pos].n++;
}

int main(){
    scanf("%d\n", &N);
    node.push_back(Node('H'));
    for(int i = 0; i < N; i++){
        getline(cin, tmp);
        addString(tmp);
    }
    DP[0] = 1;
    tar[0] = 'A';
    scanf("%s", tar + 1);
    for(int i = 1; i < strlen(tar); i++)
    {
        int pos = 0;
        for(int j = i; j <= min(i + 299, (int)strlen(tar) - 1); j++){
            if(pos != -1) pos = node[pos].next[tar[j] - 'a'];
            w[j][w_size[j]++] = pos != -1 ? node[pos].n : 0;
        }

    }
    for(int i = 1; i < strlen(tar); i++){
        for(int j = 0; j < w_size[i]; j++){
            DP[i] += DP[i - w_size[i] + j] * w[i][j];
        }
        DP[i] %= MOD;
    }
    printf("%lld", DP[strlen(tar) - 1]);
}
