/**
 * Author: gratus907
 * Date: 2021-07-26
 * Description: Finds sccs in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: tested boj 4196
 * Usage: build graph only with add_edge. use C.find_scc();
 */

vector<int> adj[10020];
vector<int> revadj[10020];
vector<vector<int>> scc;
stack<int> s;
int visited[10020];
void DFS(int node) {
	visited[node] = 1;
	for(auto N: adj[node]) {
		if(!visited[N]) {
			DFS(N);
		}
	}
	s.push(node);
}
void revDFS(int node, vector<int>& v) {
	visited[node] = 1;
	for(auto N: revadj[node]) {
		if(!visited[N]) {
			revDFS(N, v);
		}
	}
	v.push_back(node);
}
void findSCC() {
	fill(visited, visited+10002, 0);
	while(!s.empty()) {
		int tmp = s.top();
		s.pop();
		if(visited[tmp]) {
			continue;
		}
		vector<int> v;
		revDFS(tmp, v);
		sort(v.begin(), v.end());
		scc.push_back(v);
	}
}