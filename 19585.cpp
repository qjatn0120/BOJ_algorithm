#include <bits/stdc++.h>

using namespace std;

struct Node{
    Node **next = nullptr;
    char c = 'a';
    bool b = false;
};

void addStr(Node *it, string &s){
    for(char c : s){
        if(it->next == nullptr){
            it->next = new Node*[1];
            it->next[0] = new Node;
            it->c = c;
        }
        if(it->c != 'A' && it->c != c){
            Node *tmp = it->next[0];
            delete it->next;
            it->next = new Node*[26];
            for(int i = 0; i < 26; i++) it->next[i] = nullptr;
            it->next[it->c - 'a'] = tmp;
            it->c = 'A';
        }
        if(it->c == 'A' && it->next[c - 'a'] == nullptr) it->next[c - 'a'] = new Node;
        if(it->c != 'A') it = it->next[0];
        else it = it->next[c - 'a'];
    }
    it->b = true;
}

Node *head1 = new Node(), *head2 = new Node();
int C, N, Q;
bitset <2005> b1, b2;
string str;

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> C >> N;
    for(int i = 0; i < C; i++){
        cin >> str;
        addStr(head1, str);
    }
    for(int i = 0; i < N;  i++){
        cin >> str;
        reverse(str.begin(), str.end());
        addStr(head2, str);
    }
    cin >> Q;
    for(int i = 0; i < Q; i++){
        b1.reset(), b2.reset();
        cin >> str;
        Node* it = head1;
        for(int j = 0; j < str.size() - 1; j++){
            if(it->c == 'A') it = it->next[str[j] - 'a'];
            else{
                if(it->next != nullptr && it->c == str[j]) it = it->next[0];
                else break;
            }
            if(it == nullptr) break;
            if(it->b) b1.set(j);
        }
        it = head2;
        for(int j = str.size() - 1; j; j--){
            if(it->c == 'A') it = it->next[str[j] - 'a'];
            else{
                if(it->next != nullptr && it->c == str[j]) it = it->next[0];
                else break;
            }
            if(it == nullptr) break;
            if(it->b) b2.set(j - 1);
        }
        cout << ((b1 & b2).any() ? "Yes\n" : "No\n");
    }
}
