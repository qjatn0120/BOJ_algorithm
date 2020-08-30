#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, p, cnt, key;
    bool inv;
    Node(int p) : p(p){
        l = r = -1;
        cnt = 1;
        inv = false;
    }
};

struct splayTree{
    vector <Node> node;
    int root;

    void Rotate(int x){
        int p = node[x].p, b;
        int g = node[p].p;
        prop(g), prop(p), prop(x);
        if(x == node[p].l){
            node[p].l = b = node[x].r;
            node[x].r = p;
        }else{
            node[p].r = b = node[x].l;
            node[x].l = p;
        }
        node[x].p = node[p].p;
        node[p].p = x;
        if(b != -1) node[b].p = p;
        if(g != -1){
            if(node[g].l == p) node[g].l = x;
            else node[g].r = x;
        }else root = x;
        Update(p);
        Update(x);
    }

    void Splay(int x){
        prop(x);
        while(node[x].p != -1){
            int p = node[x].p;
            int g = node[p].p;
            prop(g), prop(p), prop(x);
            if(g != -1){
                if((node[p].l == x) == (node[g].l == p)) Rotate(p);
                else Rotate(x);
            }
            Rotate(x);
        }
    }

    void Update(int x){
        node[x].cnt = 1;
        if(node[x].l != -1) node[x].cnt += node[node[x].l].cnt;
        if(node[x].r != -1) node[x].cnt += node[node[x].r].cnt;
    }

    void Find_Kth(int k){
        int pos = root;
        while(1){
            prop(pos);
            if((node[pos].l == -1 ? 1 : node[node[pos].l].cnt + 1) == k) break;
            if(node[pos].l != -1 && k <= node[node[pos].l].cnt) pos = node[pos].l;
            else{
                k -= (node[pos].l == -1 ? 0 : node[node[pos].l].cnt) + 1;
                pos = node[pos].r;
            }
        }
        Splay(pos);
    }

    void Insert(int key){
        if(node.empty()){
            node.push_back(Node(-1));
            root = 0;
            node[0].key = key;
            node[0].cnt = 1;
            return;
        }
        int pos = root;
        while(1){
            if(node[pos].key == key) return;
            if(key < node[pos].key){
                if(node[pos].l == -1){
                    node[pos].l = node.size();
                    node.push_back(Node(pos));
                    break;
                }else pos = node[pos].l;
            }else{
                if(node[pos].r == -1){
                    node[pos].r = node.size();
                    node.push_back(Node(pos));
                    break;
                }else pos = node[pos].r;
            }
        }
        node[node.size() - 1].key = key;
        node[node.size() - 1].cnt = 1;
        Splay(node.size() - 1);
    }

    int Interval(int L, int R){
        if(L == 1 && R == node.size()) return root;
        if(L == 1){
            Find_Kth(R + 1);
            return node[root].l;
        }
        if(R == node.size()){
            Find_Kth(L - 1);
            return node[root].r;
        }
        Find_Kth(L - 1);
        int tmp = root;
        root = node[root].r;
        node[root].p = -1;
        Find_Kth(R - L + 2);
        node[tmp].r = root;
        node[root].p = tmp;
        root = tmp;
        return node[node[root].r].l;
    }

    void prop(int x){
        if(x == -1) return;
        if(!node[x].inv) return;
        swap(node[x].l, node[x].r);
        if(node[x].l != -1) node[node[x].l].inv = (!node[node[x].l].inv);
        if(node[x].r != -1) node[node[x].r].inv = (!node[node[x].r].inv);
        node[x].inv = false;
    }

    void print(int pos){
        prop(pos);
        //printf("%d|%d|%d|%d|%d\n", node[pos].key, pos, node[pos].l, node[pos].r, node[pos].cnt);
        if(node[pos].l != -1) print(node[pos].l);
        printf("%d ", node[pos].key);
        if(node[pos].r != -1) print(node[pos].r);
    }

    void Reverse(int L, int R){
        if(L >= R) return;
        int pos = Interval(L, R);
        node[pos].inv = (!node[pos].inv);
    }

    void DFS(vector <int>& v, int pos){
        prop(pos);
        if(node[pos].l != -1) DFS(v, node[pos].l);
        v.push_back(pos);
        if(node[pos].r != -1) DFS(v, node[pos].r);
    }
}BIT;

int N, Q, d, x, y;

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 1; i <= N; i++) BIT.Insert(i);
    for(int i = 0; i < Q; i++){
        scanf("%d %d %d", &d, &x, &y);
        if(d == 1){
            BIT.Reverse(1, x - 1);
            BIT.Reverse(x, y);
            BIT.Reverse(1, y);
        }else if(d == 2){
            BIT.Reverse(x, y);
            BIT.Reverse(y + 1, N);
            BIT.Reverse(x, N);
        }else{
            vector <int> v;
            BIT.DFS(v, BIT.Interval(x, y));
            int cnt = y - x + 1;
            vector <int> result;
            for(int i = 0; i < (cnt + 1) / 2; i++){
                result.push_back(BIT.node[v[i]].key);
                if(i + (cnt + 1) / 2 != cnt) result.push_back(BIT.node[v[i + (cnt + 1) / 2]].key);
            }
            for(int i = 0; i < cnt; i++) BIT.node[v[i]].key = result[i];
        }
    }
    BIT.print(BIT.root);
    return 0;
}
