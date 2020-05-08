#define maxn 1005050

int lcp[maxn];

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
  SA();
  Kasai();
  return 0;
}
