/**
 * Author: stet-stet
 * Date: 2022-07-18
 * License: CC0
 * Source: folklore + ac-library(modified to fit our taste)
 * Description: Interval incremental modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: tested(10999)
 */
#include<algorithm>
#include<vector>
template<class T> T defaultValue(){ return T(); }
template<class T> T defaultOperation(T a,T b){return a+b;}
template<class F, class T> T defaultMapping(F lazy, T val, int span_covered){
	return val + lazy*span_covered;
}
template<class S, class F = S,
		 S (*op)(S,S) = defaultOperation<S>, 
		 S (*mapping)(F, S, int) = defaultMapping<F,S>,
		 F (*composition)(F, F) = defaultOperation<F>, 
		 S(*e)() = defaultValue<S>,
		 F (*id)() = defaultValue<F> //tell me if there's a better way
> class Segtree{ private:
	int _n, size, log;
	std::vector<S> d;
	std::vector<F> lz;
	std::vector<int> span_covered;
	void update(int k){ d[k] = op(d[2*k], d[2*k+1]); }
	void all_apply(int k, F f){
		d[k] = mapping(f, d[k], span_covered[k]);
		if(k < size) lz[k] = composition(f,lz[k]);
	}
	void push(int k){
		all_apply(k<<1,lz[k]); all_apply((k<<1)|1, lz[k]); lz[k] = id();
	} // END PRIVATE
	public:
	explicit Segtree(int n=100000) : Segtree(std::vector<S>(n,e())) {}
	explicit Segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log=0;
        while( (1U << log) < (unsigned int)(_n)) log++;
		size = 1 << log;
		d = std::vector<S>(2*size,e());
		lz = std::vector<F>(size, id());
		span_covered = std::vector<int>(2*size,e());
		int current_span = 1;
		for(int i=0;i<_n;++i) d[size+i] = v[i];
		for(int i=size-1;i>=1;i--){update(i);}
		for(int i=2*size-1;i>=1;--i){
			span_covered[i] = current_span;
			if(size == current_span * i) current_span *= 2;
		}
	}
	S modify(int p, S x){
		p+=size;  for(int i=log;i>=1;i--) push(p>>i);
		d[p] = x; for(int i=1;i<=log;i++) update(p>>i);
	}
	S query(int l, int r) { // [l,r)
		if(l == r) return e();
		l += size; r += size;
		for(int i=log; i>=1; i--) {
			if (((l>>i)<<i)!=l) push(l>>i);
			if (((r>>i)<<i)!=r) push((r-1)>>i);
		}
		S sml=e(),smr=e();
		while(l<r){
			if(l&1) sml = op(sml, d[l++]);
			if(r&1) smr = op(d[--r], smr);
			l>>=1; r>>=1;
		}
		return op(sml,smr);
	}
	void apply(int l,int r, F f){
		if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
	}
};
