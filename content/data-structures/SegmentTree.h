/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: folklore
 * Description: Point modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Segtree
{
	int n;
	int T[2*N];
	void build(vector<int> &v)
	{
		n = v.size();
		for (int i = 0; i<n; i++)
			T[n+i] = v[i];
		for (int i = n-1; i>0; i--)
			T[i] = T[i<<1] + T[(i<<1)|1];
	}
	void modify(int pos, int val)
	{
		for (T[pos += n] = val; pos > 1; pos >>= 1)
			T[pos >> 1] = T[pos] + T[pos^1];
	}
	// query is on [l, r)!!
	int query(int l, int r)
	{
		int res = 0;
		for (l += n, r += n; l < r; l >>=1, r>>=1)
		{
			if (l & 1) res += T[l++];
			if (r & 1) res += T[--r];
		}
		return res;
	}
} S;
