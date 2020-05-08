#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(a) (int) a.size()
#define pb push_back
#define fst first
#define snd second

typedef long long int ll;
typedef unsigned long long int ull;
typedef vector <int> vi;
typedef pair <int, int> ii;
typedef pair <int, pair <int, int> > iii;

#define maxn 100505

struct no{
  int id, valor;
  no(){
    id = -1;
    valor = (-1ll<<30);
  }
  no(int valor, int id){
    this->id = id, this->valor = valor;
  }
};

int v[maxn];
ll lazy[4*maxn];
no segtree[4*maxn];

no neutral(){
  return no();
}

no combine(no a, no b){
  if(a.valor == b.valor)
    return a.id < b.id ? a : b;
  return a.valor > b.valor ? a : b;
}

void build(int i, int l, int r){
  if(l == r){
    segtree[i] = no(v[l], l+1);
    return;
  }
  int nxt = 2*i, md = (l+r)/2;
  build(nxt, l, md);
  build(nxt+1, md+1, r);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

void push(int i, int l, int r){
  if(lazy[i] != 0){
    segtree[i].valor += lazy[i];
    if(l != r){
      int nxt = 2*i;
      lazy[nxt] += lazy[i];
      lazy[nxt+1] += lazy[i];
    }
    lazy[i] = 0;
  }
}

void upt(int i, int l, int r, int x, int y, int value){
  push(i, l, r);
  if(l > y or r < x)
    return;
  if(l >= x and r <= y){
    lazy[i] += value;
    push(i, l, r);
    return;
  }
  int nxt = 2*i, md = (l+r)/2;
  upt(nxt, l, md, x, y, value);
  upt(nxt+1, md+1, r, x, y, value);
  segtree[i] = combine(segtree[nxt], segtree[nxt+1]);
}

no get(int i, int l, int r, int x, int y){
  push(i, l, r);
  if(l > y or r < x)
    return neutral();
  if(l >= x and r <= y)
    return segtree[i];
  int nxt = 2*i, md = (l+r)/2;
  return combine(get(nxt, l, md, x, y), 
        get(nxt+1, md+1, r, x, y));
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n, q;
  while(cin >> n >> q){
    for(int i = 0; i < n; i++)
      cin >> v[i];
    memset(lazy, 0, sizeof lazy);
    build(1, 0, n-1);
    while(q--){
      char op;
      cin >> op;
      if(op == 'C'){
        int x, y;
        cin >> x >> y;
        cout << get(1, 0, n-1, x-1, y-1).id << "\n";
      }
      else{
        int x, y, z;
        cin >> x >> y >> z;
        upt(1, 0, n-1, x-1, y-1, z);
      }
    }
  }
  return 0;
}
