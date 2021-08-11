#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXX = 250000;

struct Dot{
    int x, y, k;
};

int N, K;
Dot dot[MAXN];

bool cmp(Dot d1, Dot d2){
    return d1.x < d2.x;
}

// lazy seg

int tree[MAXX * 4], lazy[MAXX * 4];

void prop(int n, bool isLeaf){
    tree[n] += lazy[n];
    if(!isLeaf){
        lazy[n * 2] += lazy[n];
        lazy[n * 2 + 1] += lazy[n];
    }
    lazy[n] = 0;
}

void Update(int n, int l, int r, int nL, int nR, int c){

    if(lazy[n]) prop(n, nL == nR);

    if(l > nR || r < nL) return;

    int mid = (nL + nR) >> 1;
    if(l <= nL && nR <= r){
        lazy[n] += c;
        prop(n, nL == nR);
        return;
    }

    Update(n * 2, l, r, nL, mid, c);
    Update(n * 2 + 1, l, r, mid + 1, nR, c);

    tree[n] = max(tree[n * 2], tree[n * 2 + 1]);
}

multiset <int> color_pos[MAXN];

void update_dot(int idx, int diff, int R){

    int l = dot[idx].y, r = dot[idx].y + R; // seg tree update 범위
    int y = dot[idx].y, color = dot[idx].k;

    // l 범위를 max(l ,(y이하 중 가장 큰 것) + R + 1)로 조정
    auto it = color_pos[color].upper_bound(y);
    if(it != color_pos[color].begin()){
        l = max(l, *(--it) + R + 1);
    }

    // r 범위를 min(r, (y이상 중 가장 작은 것) - 1) 으로 조정
    it = color_pos[color].lower_bound(y);
        if(it != color_pos[color].end()){
        r = min(r, *(it) - 1);
    }

    // seg tree update
    if(l <= r) Update(1, l, r, 1, MAXX, diff);
}

bool testR(int R){
    int p1 = 0, p2 = 0; // dot[p1] ~ dot[p2 - 1] 범위의 점을 고려함

    // reset tree
    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    // reset multiset
    for(int i = 1; i <= K; i++) color_pos[i].clear();

    for(; p1 < N; p1++){

        while(p2 < N && dot[p2].x - dot[p1].x <= R){ // dot[p1:p2] 범위의 점이 R 이내에 있을 때까지 p2를 늘림

            update_dot(p2, 1, R); // dot[p2] 추가
            color_pos[dot[p2].k].insert(dot[p2].y); // multiset update
            if(tree[1] == K) return true; // dot[p1:p2] 범위에 R 정사각형 있는 지 검사
            p2++;
        }

        // dot[p1] 삭제
        color_pos[dot[p1].k].erase(color_pos[dot[p1].k].find(dot[p1].y));
        update_dot(p1, -1, R);
    }

    return false;
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    cin >> N >> K;
    for(int i = 0; i < N; i++) cin >> dot[i].x >> dot[i].y >> dot[i].k;
    sort(dot, dot + N, cmp);

    int lo = 0, hi = MAXX;

    while(lo < hi){
        int mid = (lo + hi) >> 1;
        if(testR(mid)) hi = mid;
        else lo = mid + 1;
    }

    cout << lo;
}
