struct wavelet {
	int lo, hi;
	wavelet *l, *r;
	vi b;
	wavelet(int *from, int *to, int x, int y) {
		lo = x;
		hi = y;
		if(lo == hi or from >= to){
			return;
    }
		int md = (lo+hi)/2;
		auto f = [md](int x){
			return x <= md;
		};
		b.reserve(to-from+1);
		b.pb(0);
		for(auto i = from; i != to; i++){
			b.pb(b.back()+f(*i));
    }
		auto pivot = stable_partition(from, to, f);
		l = new wavelet(from, pivot, lo, md);
		r = new wavelet(pivot, to, md+1, hi);
	}
  
	int kth(int l, int r, int k){
		if(l > r){
			return 0;
    }
		if(lo == hi){
			return lo;
    }
		int in_left = b[r]-b[l-1], lb = b[l-1], rb = b[r];
		if(k <= in_left){
			return this->l->kth(lb+1, rb, k);
    }  
		return this->r->kth(l-lb, r-rb, k-in_left);
	}
  
	int cnt(int l, int r, int k){
		if(l > r or k < lo or k > hi){
			return 0;
    }
		if(lo == hi){
			return r-l+1;
    }
		int lb = b[l-1], rb = b[r], md = (lo+hi)/2;
		if(k <= md){
			return this->l->cnt(lb+1, rb, k);
    }
		return this->r->cnt(l-lb, r-rb, k);
	}
};

int main(){
  int v[100000];
  wavelet t(v+1, v+n+1, 1, 100001);
  return 0;
}
