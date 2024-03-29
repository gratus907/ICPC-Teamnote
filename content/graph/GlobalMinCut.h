/**
 * Author: Ntopia
 * Date: Unknown
 * Source: https://github.com/ntopia/icpc-teamnote/blob/master/src/graph/general-mincut-stoer-wagner.cpp
 * Description: Find a global minimum cut in an undirected graph. (Stoer-Wagner)
 * MinCut mc; mc.init(n); for (each edge) mc.addEdge(a,b,weight); mincut = mc.solve();
 * mc.cut = $\{0,1\}^n$ describing which side the vertex belongs to.
 * Time: $O(V^3)$
 * Status: Lightly tested
 */
struct MinCutMatrix {
    int n;
    vector<vector<int>> graph;

    void init(int _n) {
        n = _n;
        graph = vector<vector<int>>(n, vector<int>(n, 0));
    }
    void addEdge(int a, int b, int w) {
        if (a == b) return;
        graph[a][b] += w;
        graph[b][a] += w;
    }

    pair<int, pair<int, int>> stMinCut(vector<int> &active) {
        vector<int> key(n);
        vector<int> v(n);
        int s = -1, t = -1;
        for (int i = 0; i < active.size(); i++) {
            int maxv = -1;
            int cur = -1;
            for (auto j : active) {
                if (v[j] == 0 && maxv < key[j]) {
                    maxv = key[j];
                    cur = j;
                }
            }
            t = s; s = cur;
            v[cur] = 1;
            for (auto j : active) key[j] += graph[cur][j];
        }
        return make_pair(key[s], make_pair(s, t));
    }

    vector<int> cut;

    int solve() {
        int res = numeric_limits<int>::max();
        vector<vector<int>> grps;
        vector<int> active;
        cut.resize(n);
        for (int i = 0; i < n; i++) grps.emplace_back(1, i);
        for (int i = 0; i < n; i++) active.push_back(i);
        while (active.size() >= 2) {
            auto stcut = stMinCut(active);
            if (stcut.first < res) {
                res = stcut.first;
                fill(cut.begin(), cut.end(), 0);
                for (auto v : grps[stcut.second.first]) cut[v] = 1;
            }

            int s = stcut.second.first, t = stcut.second.second;
            if (grps[s].size() < grps[t].size()) swap(s, t);

            active.erase(find(active.begin(), active.end(), t));
            grps[s].insert(grps[s].end(), grps[t].begin(), grps[t].end());
            for (int i = 0; i < n; i++) { graph[i][s] += graph[i][t]; graph[i][t] = 0; }
            for (int i = 0; i < n; i++) { graph[s][i] += graph[t][i]; graph[t][i] = 0; }
            graph[s][s] = 0;
        }
        return res;
    }
};