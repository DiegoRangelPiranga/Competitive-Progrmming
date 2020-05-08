/*input
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
typedef pair <ii, string> iii;

#define maxn 223456

int pai[maxn], _rank[maxn];
bool red[maxn];

int findset(int x){
	return pai[x] == x ? x : pai[x] = findset(pai[x]);
}

void joinset(int x, int y){
	int i = findset(x), j = findset(y);
	if(_rank[i] > _rank[j]){
		pai[j] = i;
		red[i] |= red[j];
	}
	else{
		pai[i] = j;
		red[j] |= red[i];
		if(_rank[i] == _rank[j])
			_rank[j]++;
	}
}

int main(){
	int n, m;
	vector <tuple <int,int,int>> edges;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++)
		pai[i] = i, _rank[i] = 0, red[i] = 0;
	for(int i = 0; i < m; i++){
		int u;
		scanf("%d", &u);
		red[u] = 1;
	}
	for(int i = 0; i < n-1; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.push_back(make_tuple(u, v, w));
	}
	sort(all(edges), [](tuple <int, int, int> a, tuple <int, int, int> b){
		return (get <2> (a)) > (get <2> (b));
	});
	ll ans = 0;
	for(auto i : edges){
		int x = get <0> (i), y = get <1> (i);
		if(red[findset(x)]+red[findset(y)] < 2)
			joinset(x, y);
		else
			ans += ((ll)get <2> (i));
	}
	printf("%lld\n", ans);
	return 0;
}