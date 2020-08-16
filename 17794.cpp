#include <bits/stdc++.h>

using namespace std;

struct Query{
    bool type;
    int a, b, dist;

    Query(int a, int b) : a(a), b(b), type(true) {}
    Query(int a, int b, int dist) : a(a), b(b), dist(dist), type(false) {}
};

bool cmp(Query q1, Query q2){
    if(q1.a == q2.a) return q1.type < q2.type;
    return q1.a > q2.a;
}

vector <Query> v;
set <pair<int, int> > st;

void update(int b, int dist){
    auto it = st.lower_bound({-b, 0});
    if(it != st.end() && it->second < dist) return;
    it = st.lower_bound({-b, INT_MAX});
    while(1){
        if(it == st.begin()) break;
        it--;
        if(it->second < dist) break;
        it = st.erase(it);
    }
    st.insert({-b, dist});
}

int query(int b){
    return st.lower_bound({-b, 0})->second;
}

int s, a, b, c;
long long int ans;

int main(){
    scanf("%d", &s);
    for(int i = 0; i < s; i++){
        scanf("%d %d", &a, &b);
        v.push_back(Query(a, b, i +  1));
    }
    scanf("%d", &c);
    for(int i = 0; i < c; i++){
        scanf("%d %d", &a, &b);
        v.push_back(Query(a, b));
    }
    sort(v.begin(), v.end(), cmp);
    for(int i = 0; i < v.size(); i++){
        if(v[i].type) ans += query(v[i].b);
        else update(v[i].b, v[i].dist);
    }
    printf("%lld", ans);
}
