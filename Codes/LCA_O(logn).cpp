#define maxn 100005
#define LOG 20

vector <pair <int, int>> g[maxn];
int dp[maxn][LOG], lvl[maxn];
long long int dist[maxn];

int LCA(int u, int v){
  if(lvl[u] > lvl[v]){
    swap(u, v);
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[v][i] != -1 and lvl[dp[v][i]] >= lvl[u]){
      v = dp[v][i];
    }
  }
  if(u == v){
    return u;
  }
  for(int i = LOG-1; i >= 0; i--){
    if(dp[u][i] != dp[v][i]){
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  return dp[v][0];
}

void dfs(int u, int p, int h, int w){
  dp[u][0] = p;
  lvl[u] = h;
  dist[u] = w;
  //calcula pais
  for(int i = 1; i < LOG; i++){
    if(dp[u][i-1] != -1){
      dp[u][i] = dp[dp[u][i-1]][i-1];
    }
  }
  for(auto v : g[u]){
    if(v.first != p){
      dfs(v.first, u, h+1, w+v.second);
    }
  }
}

int main(){
  memset(dp, -1, sizeof dp);
  dfs(0, 0, 0, 0);
  return 0;
}
