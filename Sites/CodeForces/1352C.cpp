#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

ll cnt(ll l, ll r, ll n){
  return (r/n)-(l/n)+(l%n == 0 ? 1 : 0);
}

int main(){
  int t;
  cin >> t;
  while(t--){
    int n, k;
    cin >> n >> k;
    ull l = 1, r = 10000000000000000000ull, md;
    while(l < r){
      md = l+((r-l)/2ll);
      if(md-cnt(1, md, n) < k){
        l = md+1;
      }
      else{
        r = md;
      }
    }
    cout << l << "\n";
  } 
  return 0;
}
