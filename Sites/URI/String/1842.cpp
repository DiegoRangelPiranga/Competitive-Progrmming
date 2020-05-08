#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
#define sz(x) (int) x.size()
#define debug(x) cout << "DEBUG: " << x << endl;

typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> ii;

#define maxn 100100

int suffix[maxn], RA[maxn], aux[maxn], c[maxn], lcp[maxn], invsuffix[maxn];
string pp;
int n;

void coutingsort(int k){
	memset(c, 0, sizeof c);
	int maxi = max(300, n);
	for(int i = 0; i < n; i++){
		c[RA[i+k]]++;
  }
	int sum = 0;
	for(int i = 0; i < maxi; i++){
		int aux = c[i];
		c[i] = sum;
		sum += aux;
	}
	for(int i = 0; i < n; i++){
		aux[c[RA[suffix[i]+k]]++] = suffix[i];
  }
	for(int i = 0; i < n; i++){
		suffix[i] = aux[i];
  }
}

void SA(){
	int n = pp.size();
	memset(RA, 0, sizeof RA);
	for(int i  = 0; i < n; i++){
		suffix[i] = i;
		RA[i] = pp[i];
	}
	for(int k = 1; k < n; k <<= 1){
		coutingsort(k);
		coutingsort(0);
		aux[suffix[0]] = 0;
		int newRa = 0;
		for(int i = 1; i < n; i++){
			if(RA[suffix[i]] == RA[suffix[i-1]] and 
				RA[suffix[i]+k] == RA[suffix[i-1]+k]){
				aux[suffix[i]] = newRa;
      }
			else{
				aux[suffix[i]] = ++newRa;
      }
		}
		for(int i = 0; i < n; i++){
			RA[i] = aux[i];
    }
		if(RA[suffix[n-1]] == n-1){
			break;
    }
	}
}

void kasai(){
	lcp[n-1] = 0;
	for(int i = 0; i < n; i++){
		invsuffix[suffix[i]] = i;
  }
	int k = 0;
	for(int i = 0; i < n; i++){
		if(invsuffix[i] == n-1){
			k = 0;
			continue;
		}
		int j = suffix[invsuffix[i]+1];
		while(i+k < n and j+k < n and pp[i+k] == pp[j+k]){
			k++;
    }
		lcp[invsuffix[i]] = k;
		if(k){
			k--;
    }
	}
}

int main(){
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
  /*int nn;
  cin >> nn;
  vector <string> vs(nn);
  for(int i = 0; i < nn; i++){
    cin >> vs[i];
  }
  string p;
  cin >> p;
  for(auto &i : vs){
    while(i.find(p) != string::npos){
      auto y = i.find(p);
      i.erase(i.begin()+y, i.begin()+y+sz(p));
    }
  }
  for(auto i : vs){
    pp = pp+i+"$";
  }*/
	cin >> pp;
  pp += "$";
  n = sz(pp);
  SA();
  kasai();
  ii ans = {0, 0};
  for(int i = 0; i < sz(pp); i++){
    if(lcp[i] > ans.first){
      ans = {lcp[i], i};
    }
  }
  if(ans.first > 2){
    for(int i = suffix[ans.second]; i < suffix[ans.second]+ans.first; i++){
      cout << pp[i];
    }
    cout << "\n";
  }
  else{
    cout << "*" << "\n";
  }
  //vector <string> ans;
  //for(int i = 0; i < n; i++){
		//cout << suffix[i] << "\n";
		//cout << pp.substr(suffix[i]) << "\n";  
    //cout << lcp[i] << " " << pp.substr(suffix[i]) << " and " << pp.substr(suffix[i+1])<< "\n";
    /*if(lcp[i]-1 == nn){
      string t;
      for(int j = suffix[i]; j < suffix[i]+nn; j++){
        t+= pp[j];
      }
      ans.push_back(t);
    }*/
  //}
  //sort(all(ans));
  //cout << ans[0] << "\n";
  return 0;
}
