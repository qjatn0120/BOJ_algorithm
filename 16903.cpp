#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node(){
        cnt = 0;
        nxt.push_back(-1);
        nxt.push_back(-1);
    }
    int cnt;
    vector <int> nxt;
};

struct Trie{

    vector <Node> node;

    Trie(){
        node.push_back(Node());
    }

    void Add(int x){
        int pos = 0;
        for(int i = 29; i >= 0; i--){
            int nxtPos = (x & (1 << i)) ? 1 : 0;
            if(node[pos].nxt[nxtPos] == -1){
                node[pos].nxt[nxtPos] = node.size();
                node.push_back(Node());
            }
            pos = node[pos].nxt[nxtPos];
            node[pos].cnt++;
        }
    }

    void Delete(int x){
        int pos = 0;
        for(int i = 29; i >= 0; i--){
            pos = node[pos].nxt[(x & (1 << i)) ? 1 : 0];
            node[pos].cnt--;
        }
    }

    int Query(int x){
        int pos = 0, ret = 0;
        for(int i = 29; i >= 0; i--){
            int nxtPos = node[pos].nxt[(x & (1 << i)) ? 0 : 1];
            if(nxtPos == -1 || node[nxtPos].cnt == 0) nxtPos = node[pos].nxt[(x & (1 << i)) ? 1 : 0];
            else ret += (1 << i);
            pos = nxtPos;
        }
        return ret;
    }

}trie;

int M, t, x;

int main(){
    trie.Add(0);
    scanf("%d", &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &t, &x);
        if(t == 1) trie.Add(x);
        else if(t == 2) trie.Delete(x);
        else printf("%d\n", trie.Query(x));
    }
}
