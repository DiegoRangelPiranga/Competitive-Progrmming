#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;
 
typedef long long int ll;
typedef unsigned long long int ull;
typedef vector <int> vi;
typedef pair <ll, ll> ii;
typedef pair <ll, ii> iii;

struct no{
  bool end;
  int cnt;
  no *g[27];
  no(){
    cnt = 1;
    end = false;
    for(int i = 0; i < 27; i++)
      g[i] = NULL;
  }
};

no* Trie;

void add(string s){
  no *p = Trie;
  for(auto i : s){
    int u = i-'a';
    if(p->g[u] == NULL)
      p->g[u] = new no();
    else
      p->g[u]->cnt++;
    p = p->g[u];
  }
  p->end = true;
}

int _find(string s){
  no *p = Trie;
  int last = 0, len = sz(s);
  for(auto i : s){
    int u = i-'a';
    if(!p->g[u])
      return sz(s);
    if(p->g[u]->cnt == last){
      len--;
    }
    last = p->g[u]->cnt;
    p = p->g[u];
    
  }
  return len;
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  int n;
  while(cin >> n){
    Trie = new no();
    vector <string> words;
    for(int i = 0; i < n; i++){
      string s;
      cin >> s;
      words.push_back(s);
      add(s);
    }
    double ans = 0;
    for(auto i : words)
      ans += _find(i);
    cout << fixed << setprecision(2) << ans/sz(words) << endl;
  }
  return 0;
}
