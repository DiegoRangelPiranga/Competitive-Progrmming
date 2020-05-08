#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <int, int> ii;
typedef vector <int> vi;
typedef vector <ii> vii;

#define maxn 20005

int segtree[4*maxn], lazy[4*maxn];

void lazyprop(int i, int l, int r){
    if(lazy[i]){
        segtree[i] = max(segtree[i], lazy[i]);
        if(l != r){
            int nxt = 2*i;
            lazy[nxt] = max(lazy[nxt], lazy[i]);
            lazy[nxt+1] = max(lazy[nxt+1], lazy[i]);
        }
        lazy[i] = 0;
    }
}

void update(int i, int l, int r, int x, int y, int v){
    lazyprop(i, l, r);
    if(l > y or r < x)
        return;
    if(l >= x and r <= y){
        lazy[i] = max(lazy[i], v);
        lazyprop(i, l, r);
        return;
    }
    int md = (l+r)/2, nxt = 2*i;
    update(nxt, l, md, x, y, v);
    update(nxt+1, md+1, r, x, y, v);
    segtree[i] = max(segtree[nxt], segtree[nxt+1]);
}

int get(int i, int l, int r, int x, int y){
    lazyprop(i, l, r);
    if(l > y or r < x)
        return 0;
    if(l >= x and r <= y)
        return segtree[i];
    int md = (l+r)/2, nxt = 2*i;
    return max(get(nxt, l, md, x, y), get(nxt+1, md+1, r, x, y));    
}

int main(){
    int l, h, r;
    int mx = 0;
    while(scanf("%d %d %d", &l, &h, &r) != EOF){
        update(1, 0, maxn-1, l, r-1, h);
        mx = max(mx, r);
    }
    int last = -1;
    vector <ii> ans;
    for(int i = 1; i <= mx; i++){
        int var = get(1, 0, maxn, i, i);
        if(var != last){
            last = var;
            ans.push_back({i, var});
        }
    }
    for(int i = 0; i < sz(ans); i++)
        printf("%d %d%s", ans[i].first, ans[i].second, i+1 == sz(ans) ? "\n" : " ");
    return 0;
}
