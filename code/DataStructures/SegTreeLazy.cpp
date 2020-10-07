struct SegTree
{
    int n;
    vector <int> segtree;
    vector <int> lazy;
    SegTree(vector <int> &data)
    {
        n = data.size();
        segtree.resize(4*n);
        lazy.resize(4*n);
        init(data,1,0,n-1);
    }
    int init(vector <int> &data, int node, int l, int r)
    {
        if (l==r)
        {
            segtree[node] = data[l];
            return segtree[node];
        }
        int mid = (l+r)/2;
        int ls = init(data,node*2,l,mid);
        int rs = init(data,node*2+1,mid+1,r);
        segtree[node] = (ls+rs);
        return segtree[node];
    }
    void propagation(int node, int nl, int nr)
    {
        if (lazy[node]!=0)
        {
            segtree[node] += (lazy[node] * (nr-nl+1));
            if (nl != nr)
            {
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    //range_upd(s,e,k,1,0,n-1);
    void range_upd(int s, int e, int k, int node, int nl, int nr)
    {
        propagation(node,nl,nr);

        if (nr < s || nl > e)
            return;
        if (s <= nl && nr <= e)
        {
            lazy[node] += k;
            propagation(node,nl,nr);
            return;
        }
        int mid = (nl + nr)/2;
        range_upd(s,e,k,node*2,nl,mid);
        range_upd(s,e,k,node*2+1,mid+1,nr);
        segtree[node] = segtree[node*2] + segtree[node*2+1];
        return;
    }
    //sum(s,e,1,0,n-1)
    int sum(int s, int e, int node, int nl, int nr)
    {
        propagation(node,nl,nr);
        if (nr < s || nl > e)
            return 0;
        if (s <= nl && nr <= e)
        {
            return segtree[node];
        }
        int mid = (nl+nr)/2;
        return (sum(s,e,node*2,nl,mid) + sum(s,e,node*2+1,mid+1,nr));
    }
};
