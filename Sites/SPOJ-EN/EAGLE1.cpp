#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(args...){string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args);}
#define endl "\n"

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

void err(istream_iterator<string> it){}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args){
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}

#define maxn 105001

vector <ii> g[maxn];
long long dist[2][maxn];
int n;

pair <int, long long> bfs(int u, int sd){
  queue <int> q;
  for(int i = 1; i <= n; i++){
    dist[sd][i] = (1LL<<50);
  }
  dist[sd][u] = 0;
  q.push(u);
  while(!q.empty()){
    u = q.front();
    q.pop();
    for(auto v : g[u]){
      if(dist[sd][v.first] == (1LL<<50)){
        dist[sd][v.first] = dist[sd][u]+v.second;
        q.push(v.first);
      }
    }
  }
  pair <int, ll> ans = {-1, -1};
  for(int i = 1; i <= n; i++){
    if(dist[sd][i] > ans.second){
      ans = {i, dist[sd][i]};
    }
  }
  return ans;
}

int main(){
  cin.tie(NULL), cout.tie(NULL), ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--){
    cin >> n;
    for(int i = 0; i < n-1; i++){
      int u, v, w;
      cin >> u >> v >> w;
      g[u].push_back({v, w});
      g[v].push_back({u, w});
    }
    int diamU = bfs(1, 0).first;
    int diamV = bfs(diamU, 1).first;
    bfs(diamV, 0);
    for(int i = 1; i <= n; i++){
      cout << max(dist[0][i], dist[1][i]) << (i == n ? "\n" : " ");
    }
    for(int i = 1; i <= n; i++){
      g[i].clear();
    }
  }
  return 0;
}
