#define maxn 100005
#define LOG 20
 
vector <int> g[maxn];
int dp[maxn][LOG], arr[maxn], lvl[maxn], subtree[maxn];
int head[maxn], chain[maxn], posarr[maxn], inhld[maxn];
int cnt, pos;

void hld(int u, int p, int var){
  if(head[cnt] == -1){
    head[cnt] = u;
  }
  chain[u] = cnt;
  posarr[u] = pos;
  inhld[pos++] = var;
  int id = -1, sz = -1;
  for(auto v : g[u]){
    if(v != p and subtree[v] > sz){
      sz = subtree[v];
      id = v;
    }
  }
  if(id != -1){
    hld(id, u, arr[id]);
  }
  for(auto v : g[u]){
    if(v != p and v != id){
      cnt++;
      hld(v, u, arr[v]);
    }
  }
}
 
void dfs(int u, int p, int h){
  dp[u][0] = p;
  lvl[u] = h;
  subtree[u] = 1;
  for(int i = 1; i < LOG; i++){
    if(dp[u][i-1] != -1){
      dp[u][i] = dp[dp[u][i-1]][i-1];
    }
  }
  for(auto v : g[u]){
    if(v != p){
      dfs(v, u, h+1);
      subtree[u] += subtree[v];
    }
  }
}
 
int lca(int u, int v){
  if(lvl[u] > lvl[v]){
    swap(u, v);
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[v][i] != -1 and lvl[dp[v][i]] >= lvl[u]){
      v = dp[v][i];
    }
  }
  if(u == v){
    return v;
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[v][i] != dp[u][i]){
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  return dp[v][0];
}
 
long long int solveQuery(int u, int v){
  int chainU = chain[u], chainV = chain[v];
  long long int ans = 0;
  while(true){
    chainU = chain[u];
    if(chainU == chainV){
      ans = query(1, 0, pos-1, posarr[v], posarr[u]);
      //estrutura de dados O(log n)
      break;
    }
    ans = query(1, 0, pos-1, posarr[head[chainU]], posarr[u]);
    u = head[chainU];
    u = dp[u][0];
  }
  return ans;
}
 
void solveUpdate(int u, int v, int var){
  int chainU = chain[u], chainV = chain[v];
  while(true){
    chainU = chain[u];
    if(chainU == chainV){
      update(1, 0, pos-1, posarr[v], posarr[u], var);
      break;
    }
    update(1, 0, pos-1, posarr[head[chainU]], posarr[u]+1, var);
    u = head[chainU];
    u = dp[u][0];
  }
}
 
long long int solveQuery(int u, int v, int _lca){
  if(u != _lca and v != _lca){
    solveQuery(u, _lca);
    solveQuery(v, _lca);
    solve(_lca, _lca); // esse carinha pode ser problema xP 
  }
  if(u == _lca){
    return solveQuery(v, u);
  }
  return solveQuery(u, v);
}
 
void solveUpdate(int u, int v, int _lca, int var){
  if(u != _lca and v != _lca){
    solveUpdate(u, _lca, var);
    solveUpdate(v, _lca, var);
  }
  else if(u == _lca){
    solveUpdate(v, u, var);
  }
  else{
    solveUpdate(u, v, var);
  }
}
int main(){
  //... valor esta em inhld[posarr[i]]
  memset(dp, -1, sizeof dp);
  memset(head, -1, sizeof  head);
  cnt = pos = 0;
  dfs(0, 0, 0);
  hld(0, 0, arr[0]);
  build(1, 0, pos-1);
  return 0;
}
