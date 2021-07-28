/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: idk
 * Description: greater(s,e,k,1,0,n) returns number of elements strictly greater than $k$ in range $[s, e]$.
 * Pay attention to INTERVAL INCLUSIVENESS!!!
 * Time: $O(\log N)$.
 * Status: Stress-tested
 */

#define MAXN (1<<18)
#define ST (1<<17)
struct merge_sort_tree
{
	vector <int> tree[MAXN];
	int n;
	void construct (vector <int> data)
	{
		n = 1;
		while(n < data.size()) n <<= 1;
		for (int i = 0; i<data.size(); i++)
			tree[i+n] = {data[i]};
		for (int i = data.size(); i<n; i++)
			tree[i+n] = {};
		for (int i = n-1; i>0; i--)
		{
			tree[i].resize(tree[i*2].size()+tree[i*2+1].size());
			for (int p = 0, q = 0, j = 0; j < tree[i].size(); j++)
			{
				if (p == tree[i*2].size() ||
				(q<tree[i*2+1].size() && tree[i*2+1][q]<tree[i*2][p]))
					tree[i][j] = tree[i*2+1][q++];
				else tree[i][j] = tree[i*2][p++];
			}
		}
	}
	//greater(s,e,k,1,0,n)
	int greater(int s, int e, int k, int node, int ns, int ne)
	{
		if (ne <= s || ns >= e)
			return 0;
		if(s <= ns && ne <= e)
			return tree[node].end() - upper_bound(all(tree[node]), k);
		int mid = (ns+ne)>>1;
		return greater(s,e,k,node*2,ns,mid) +
		 greater(s,e,k,node*2+1,mid,ne);
	}
};
