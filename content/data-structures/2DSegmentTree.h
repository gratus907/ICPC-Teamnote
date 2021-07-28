/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: idk
 * Description: Compute sum of rectangle $[a, b) \times [c, d)$ and point modification
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

auto gif = [](int a, int b){return a+b;};
class SEG2D
{
public:
	int n;
	int m;
	vector <vector <int>> tree;
	SEG2D(int n = 0, int m = 0)
	{
		tree.resize(2*n);
		for (int i = 0; i<2*n; i++) tree[i].resize(2*m);
		this->n = n;
		this->m = m;
	}
	SEG2D(int n, int m, vector<vector<int>> &data)
	{
		tree.resize(2*n);
		for (int i = 0; i<2*n; i++) tree[i].resize(2*m);
		this->n = n;
		this->m = m;
		init(data);
	}
	void init(vector <vector <int>> & data)
	{
		n = data.size();
		m = data.front().size();
		tree = vector<vector<int>>(2*n, vector<int>(2*m, 0));
		for (int i = 0; i<n; i++)
			for (int j = 0; j<m; j++)
				tree[i+n][j+m] = data[i][j];
		for (int i = n; i<2*n; i++)
			for (int j = m-1; j>0; j--)
				tree[i][j] = gif(tree[i][j*2], tree[i][j*2+1]);
		for (int i = n-1; i>0; i--)
			for (int j = 1; j<2*m; j++)
				tree[i][j] = gif(tree[i*2][j], tree[i*2+1][j]);
	}
	void update(int x, int y, int val)
	{
		tree[x+n][y+m] = val;
		for(int i = y+m; i > 1; i /= 2)
			tree[x+n][i/2] = gif(tree[x+n][i] , tree[x+n][i^1]);
		for (int i = x+n; i>1; i/=2)
			for (int j = y+m; j>=1; j/=2)
				tree[i/2][j] = gif(tree[i][j] , tree[i^1][j]);
	}
	int query_1D(int x, int yl, int yr)
	{
		int res = 0;
		int u = yl+m, v = yr+m+1;
		for(; u<v; u/=2, v/=2)
		{
			if (u & 1)
				res = gif(res, tree[x][u++]);
			if (v & 1)
				res = gif(res, tree[x][--v]);
		}
		return res;
	}
	int query_2D(int xl, int xr, int yl, int yr)
	{
		int res = 0;
		int u = xl+n, v = xr+n+1;
		for(; u<v; u/=2, v/=2)
		{
			if (u & 1)
			{
				int k = query_1D(u++, yl, yr);
				res = gif(res, k);
			}
			if (v & 1)
			{
				int k = query_1D(--v, yl, yr);
				res = gif(res, k);
			}
		}
		return res;
	}
};
