/**
 * Author: Lee Jaechan
 * Date: 2018-08-26
 * Source: https://www.acmicpc.net/source/share/49dedc7e405249d797375b90f3122e5f
 * Description: 
 * Time: O(V+E)
 * Status: Tested on BOJ 11266
 */

const int MX = 100000;
vector<int> adj[MX];
int num[MX], low[MX], parent[MX];
bool isarti[MX];
int ind = 1;
int dfs(int u, bool isroot) {
	num[u] = low[u] = ind++;
	int childcnt = 0;
	for(int a: adj[u]) {
		if(a == parent[u]) continue;
		if(num[a]) {
			low[u] = min(low[u], num[a]);
		} else {
			parent[a] = u;
			childcnt++;
			low[u] = min(low[u], dfs(a, false));
			if(low[a] >= num[u])
				isarti[u] = true;
		}
	}
	if(isroot) isarti[u] = (childcnt>=2);
	return low[u];
}