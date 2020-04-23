#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;
 
typedef long long int ll;
typedef unsigned long long int ull;
typedef vector <int> vi;
typedef pair <int, int> ii;

#define maxn 200005

vi g[maxn];
vector <ll> fun;

ll dfs(int u, int p, ll lvl){
  ll subtree = 1;
  for(auto v : g[u]){
    if(v != p){
      subtree += dfs(v, u, lvl+1);
    }
  }
  fun.push_back(subtree-lvl);
  return subtree;
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0, 0, 1);
  sort(all(fun), greater <ll>());
  cout << accumulate(fun.begin(), fun.begin()+(n-k), 0ll) << "\n";
  return 0;
}
