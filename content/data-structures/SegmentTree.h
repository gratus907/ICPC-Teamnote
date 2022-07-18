/**
 * Author: stet-stet
 * Date: 2022-07-18
 * License: CC0
 * Source: folklore
 * Description: Point modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: tested(2042)
 */
#include<algorithm>
#include<vector>
template<class T>
T defaultValue(){ return T(); }

template<class T>
T defaultOperation(T a,T b){return a+b;}

template <class S,S (*op)(S,S) = defaultOperation<S>,S (*e)() = defaultValue<S> > 
struct segtree{ private:
    int _n, size, log; std::vector<S> d; //if you need speed go use fenwick
    void update(int k){ d[k] = op(d[k<<1],d[(k<<1)|1]); }
    public:
    explicit segtree(int n=1000000) : segtree(std::vector<S>(n,e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log=0;
        while( (1U << log) < (unsigned int)(_n)) log++;
        size = 1<<log;
        d = std::vector<S>(2*size,e());
        for (int i=0;i<_n;++i) d[size+i] = v[i];
        for(int i=size-1;i>=1;--i){
            update(i);
        }
    }
    S get(int pos){return d[pos+size]; }
    void modify(int pos, S val){
        for (d[pos += size] = val; pos > 1; pos >>= 1)
            d[pos >> 1] = op(d[pos], d[pos^1]);
    }
    S query(int l, int r){ //[l,r)
        S res = e(); // CAUTION
        for(l += size, r += size; l < r; l>>=1, r>>=1){
            if(l & 1) res = op(d[l++], res);
            if(r & 1) res = op(res, d[--r]);
        }
        return res;
    }
};

