#define maxn 100100

int suffix[maxn], RA[maxn], aux[maxn], c[maxn], invsuffix[maxn];
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
