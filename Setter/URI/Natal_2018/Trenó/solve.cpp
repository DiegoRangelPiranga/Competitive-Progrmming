/*input
7 11
0 1 15
0 2 53
1 2 40
1 3 46
2 4 31
2 5 29
3 4 3
4 5 29
3 6 11
4 6 8
5 6 40
7
0 1
0 3
0 6
2 4
4 6
5 1
1 1
*/


#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long int ll;
typedef unsigned long long int ull;
typedef vector <int> vi;
typedef pair <int, int> ii;
typedef pair <int, ii> iii;

#define maxn 123456
#define LOG 20

vector <ii> g[maxn];
int p[maxn], r[maxn];
int pai[maxn][20], ans[maxn][20], lvl[maxn];

int ffind(int x){
	return p[x] == x ? x : p[x] = ffind(p[x]);
}

int same(int x, int y){
	return ffind(x) == ffind(y);
}

int join(int x, int y){
	if(!same(x, y)){
		int i = ffind(x), j = ffind(y);
		if(r[i] > r[j])
			p[j] = i;
		else{
			p[i] = j;
			if(r[j] == r[i])
				r[j]++;
		}
	}
}

void dfs(int u, int p, int h, int w){
	pai[u][0] = p;
	lvl[u] = h;
	ans[u][0] = w;
	for(int i = 1; i < LOG; i++)
		if(pai[u][i-1] != -1)
			pai[u][i] = pai[pai[u][i-1]][i-1], ans[u][i] = max(ans[u][i-1], ans[pai[u][i-1]][i-1]);
	for(auto i : g[u])
		if(i.first != p)
			dfs(i.first, u, h+1, i.second);
}

int LCA(int u, int v){
	int resp = 0;
	if(lvl[u] > lvl[v])
		swap(u, v);
	for(int i = LOG-1; i >= 0; i--)
		if(pai[v][i] != -1 and lvl[pai[v][i]] >= lvl[u])
			resp = max(resp, ans[v][i]), v = pai[v][i];
	if(u == v)
		return resp;
	for(int i = LOG-1; i >= 0; i--)
		if(pai[u][i] != pai[v][i])
			resp = max({resp, ans[v][i], ans[u][i]}), u = pai[u][i], v = pai[v][i];
	return max({resp, ans[u][0], ans[v][0]});
}

int main(){
	int n, m, q;
	vector <iii> edges;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.push_back({u, {v, w}});
	}
	sort(all(edges), [](iii a, iii b){
		return a.second.second < b.second.second;
	});
	for(int i = 0; i <= n; i++)
		p[i] = i, r[i] = 0;
	for(auto i : edges){
		int u = i.first, v = i.second.first, w = i.second.second;
		if(!same(u, v)){
			join(u, v);
			g[u].push_back({v, w});
			g[v].push_back({u, w});
		}
	}
	memset(pai, -1, sizeof pai);
	dfs(0, 0, 0, 0);
	scanf("%d", &q);
	while(q--){
		int u, v;
		scanf("%d %d", &u, &v);
		printf("%d\n", LCA(u, v));
	}
	return 0;
}