/**
 * Author: stet-stet
 * Date: 2022-07-18
 * License: CC0
 * Source: folklore + ac-library(modified to fit our taste)
 * Description: Interval incremental modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: tested(13544)
 */
#include<algorithm>
#include<vector>
template<class T> T defaultValue(){ return T(); }
template<class T> T defaultOperation(T a,T b){return a+b;}
template <class S,S (*e)() = defaultValue<S> > 
struct Node{
    Node *l, *r;
    long long v;
    Node(){l=r=nullptr;v=e();}
};
template <class S,S (*op)(S,S) = defaultOperation<S>,S (*e)() = defaultValue<S> > 
class PST{ private:
    using NN = Node<S,e>;
    std::vector< NN* > d;
    int log, sz, _n;
    void build(NN *node, const std::vector<S>& x,int start,int end){
        if(start==end && start<x.size()){ node->v = x[start]; return;}
        else if(start==end){node->v = e(); return;} //
        int m = (start+end)>>1;
        node->l = new NN(); node->r = new NN();
        build(node->l,x,start,m); build(node->r,x,m+1,end);
        node->v = op(node->l->v,node->r->v);
    }
    void _a(NN *prv, NN *now, int start, int end, int x, int v){
        if(start==end){now->v=v; return;}
        int m=(start+end)>>1;
        if(x<=m){
            now->l = new NN(); now->r = prv->r;
            _a(prv->l, now->l, start, m, x, v);
        } else {
            now->l = prv->l; now->r = new NN();
            _a(prv->r,now->r,m+1,end,x,v);
        }
        now->v = op(now->l->v,now->r->v);
    }
    S _q(NN* node, int start, int end, int l, int r){ //query, [l,r)
        if(r<start || end<l) return 0;
        if(l<=start && end<=r) return node->v;
        int m = (start+end)>>1;
        return op(_q(node->l, start, m, l, r),_q(node->r,m+1,end,l,r));
    }
    public:
    explicit PST(int n=100000): PST(std::vector<S>(n,e())) {}
    explicit PST(const std::vector<S>& x) : _n(int(x.size())){
        log=0;
        while( (1U << log) < (unsigned int)(_n)) log++;
        sz = 1<<log;
        d.emplace_back(new NN()); build(d[0],x,0,sz-1);
    }
    void add(int loc, int v){
        d.emplace_back(new NN()); _a(d[d.size()-2],d.back(), 0, sz-1, loc, v); 
    }  
    S query(int treeidx, int l, int r){ return _q(d[treeidx], 0, sz-1, l, r-1); }
    int size(){return d.size();}
};