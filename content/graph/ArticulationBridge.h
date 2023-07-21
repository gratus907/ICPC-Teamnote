/**
 * Author: Lee Jaechan
 * Date: 2018-08-26
 * Source: https://www.acmicpc.net/source/share/cf7877570d6c4d60bcb084cf59fd38ac
 * Description: 
 * Time: O(V+E)
 * Status: Tested on BOJ 11400
 */

const int MX = 100000;
vector<int> adj[MX];
int num[MX], low[MX], parent[MX];
int ind = 1;
vector<pair<int, int>> ans;
int dfs(int u, bool isroot) {
	num[u] = low[u] = ind++;
	int childcnt = 0;
	for(int a: adj[u]) {
		if(a == parent[u]) continue;
		if(num[a]) {
			low[u] = min(low[u], num[a]);
		} else {
			childcnt++;
			parent[a] = u;
			low[u] = min(low[u], dfs(a, false));
			if(low[a] > num[u])
				ans.emplace_back(min(a,u), max(a,u));
		}

	}
	return low[u];
}