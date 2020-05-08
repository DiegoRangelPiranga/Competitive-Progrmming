#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

struct node{
	int v;
	node *l, *r;
	node(){
		v = 0;
		l = r = NULL;
	}	
};

#define maxn 100005

vector <node*> trees;
int v[maxn];

void build(node *tree, int l, int r){
	if(l == r){
		tree->v = v[l];
		return;
	}
	int md = (l+r)/2;
	tree->l = new node();
	tree->r = new node();
	build(tree->l, l, md);
	build(tree->r, md+1, r);
	tree->v = tree->l->v+tree->r->v;
}

void update(node *lastTree, node *curTree, int l, int r, int p, int var){
	if(l > p or r < p){
		return;
	}
	if(l == p and r == p){
		curTree-> v = var;
		return;
	}
	int md = (l+r)/2;
	if(p <= md){
		curTree->r = lastTree->r;
		curTree->l = new node();
		update(lastTree->l, curTree->l, l, md, p, var);
	}
	else{
		curTree->l = lastTree->l;
		curTree->r = new node();
		update(lastTree->r, curTree->r, md+1, r, p, var);
	}
	curTree->v = curTree->l->v+curTree->r->v;
}

int get(node *tree, int l, int r, int x, int y){
	if(l > y or r < x){
		return 0;
	}
	if(l >= x and r <= y){
		return tree->v;
	}
	int md = (l+r)/2;
	return get(tree->l, l, md, x, y)+get(tree->r, md+1, r, x, y);
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		for(int i = 0; i < n; i++){
			cin >> v[i];
		}
		trees.push_back(new node());
		build(trees[sz(trees)-1], 0, n-1);
		int q;
		cin >> q;
		while(q--){
			int op;
			cin >> op;
			//debug("OK");
			if(op&1){
				int x, y, k;
				cin >> x >> y >> k;
				x--, y--;
				cout << get(trees[k], 0, n-1, x, y) << "\n";
			}
			else{
				int x, w;
				cin >> x >> w;
				x--;
				trees.push_back(new node());
				update(trees[sz(trees)-2], trees[sz(trees)-1], 0, n-1, x, w);
			}
		}
		trees.clear();
	}
  return 0;
}
