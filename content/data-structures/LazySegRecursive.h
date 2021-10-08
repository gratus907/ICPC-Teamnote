/**
 * Author: DHDroid
 * Date: 2021-10-08
 */
struct SegTree {
	vector<ll> tree;
	vector<ll> lazy;
	SegTree(int n) {
		tree.resize(4*n, 0);
		lazy.resize(4*n, 0);
	}
	ll init(vector<ll>& v, int node, ll l, ll r) {
		if(l==r) 
			return tree[node] = v[l];
		else {
			ll mid = (l+r) >> 1;
			return tree[node] = init(v, 2*node, l, mid) + init(v, 2*node+1, mid+1, r); 
		}
	}
	void propagate(int node, ll l, ll r) {
		tree[node] += lazy[node] * (r-l+1LL);
		lazy[2*node] += lazy[node];
		lazy[2*node + 1] += lazy[node];
		lazy[node] = 0;
	}
    // add on [s, e]
	ll update(int node, ll l, ll r, ll s, ll e, ll v) {
		if(s <= l && e >= r) {
			lazy[node] += v;
			return tree[node] + lazy[node] * (r-l+1LL);
		}
		else if(e < l || s > r)
			return tree[node] + lazy[node] * (r-l+1LL);
		else {
			propagate(node, l, r);
			ll mid = (l+r) >> 1;
			return tree[node] = update(2*node, l, mid, s, e, v) + update(2*node+1, mid+1, r, s, e, v); 
		}
	}
	ll query(int node, ll l, ll r, ll s, ll e) {
		if(s <= l && e >= r)
			return tree[node] + lazy[node] * (r-l+1LL);
		else if(e < l || s > r)
			return 0;
		else {
			propagate(node, l, r);
			ll mid = (l+r) >> 1;
			return query(2*node, l, mid, s, e) + query(2*node+1, mid+1, r, s, e); 
		}
	}
};