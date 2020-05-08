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

int main(){
    int l, r, h;
    vi X, p;
    map <int, bool> done;
    map <int, vi> open, close;
    while(scanf("%d %d %d", &l, &h, &r) != EOF){
        p.push_back(h);
        X.push_back(l);
        X.push_back(r);
        open[l].push_back(sz(p)-1);
        close[r].push_back(sz(p)-1);
    }
    sort(all(X));
    X.erase(unique(all(X)), X.end());
    set <ii> sweep;
    ii cur = {-1, -1};
    vector <ii> ans;
    int sw = 0;
    for(auto i : open[X[0]])
        sweep.insert({p[i], i});
    while(sw < sz(X)){
        if(sz(sweep) == 0){
            sweep.insert({0, X[sw]});
        }
        int _h = sweep.rbegin()->first, id = sweep.rbegin()->second;
        if(_h != cur.first){
            cur.first = _h;
            cur.second = X[sw];
            ans.push_back(cur);
        }
        if(done.count(X[sw]))
            sw++;
        if(open.count(X[sw])){
            for(auto i : open[X[sw]])
                sweep.insert({p[i], i});
        }
        if(close.count(X[sw])){
            for(auto i : close[X[sw]]){
                if(sweep.find({p[i], i}) == sweep.end())
                    break;
                sweep.erase(sweep.find({p[i], i}));
            }
        }
        done[X[sw]] = true;
    }
    for(int i = 0; i < sz(ans); i++)
        printf("%d %d%s", ans[i].second, ans[i].first, i+1 == sz(ans) ? "\n" : " ");
    return 0; 
}
