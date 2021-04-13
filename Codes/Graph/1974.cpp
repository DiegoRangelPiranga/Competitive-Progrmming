#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define endl "\n"

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 101054

int p[maxn];

void start(int n){
	for(int i = 0; i <= n; i++)
		p[i] = i;
}

int finds(int u){
	return p[u] == u ? u : p[u] = finds(p[u]);
}

void merge(int u, int v){
	p[finds(u)] = finds(v);
}

int process(string a, string b){
	int n = sz(a), m = sz(b);
	int dp[n+1][m+1];
	memset(dp, 0, sizeof dp);
	for(int i = n-1; i >= 0; i--)
		for(int j = m-1; j >= 0; j--)
			if(a[i] == b[j])
				dp[j][i] = 1+dp[j+1][i+1];	
	int ans = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			ans = max(ans, dp[i][j]);
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	vector <int> d(n+1, 0);
	vector <tuple <int, int, int>> ed;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		ed.push_back(make_tuple(0, u, v));
		d[u]++;
		d[v]++;
	}
	sort(all(d), greater <int>());
	ll k = -1;
	ll a = 0, b = 0;
	for(int i = 0, j = 1; i < n; i++, j++)
		if(d[i] >= j-1)
			k = j;
	for(int i = 0; i < k; i++)
		a += d[i];
	for(int i = k; i < n; i++)
		b += d[i];
	if(a-b == k*(k-1)){
		vector <string> vs(n);
		for(auto &i : vs)
			cin >> i;
		for(auto &[w, u, v] : ed)
			w = process(vs[u-1], vs[v-1]);	
		sort(all(ed));
		ll ans = 0;
		start(n);
		int cnt = 0;
		for(auto &[w, u, v] : ed){
			if(finds(u) != finds(v)){
				ans += w;
				merge(u, v);
				cnt++;
			}
		}
		if(cnt == n-1){
			cout << ":]" << endl;
			cout << k << " " << n-k << " " << ans << endl;
		}
		else
			cout << ":[" << endl;
	}
	else
		cout << ":[" << endl;
	return 0;
}
