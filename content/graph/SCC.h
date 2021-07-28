/**
 * Author: gratus907
 * Date: 2021-07-26
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: tested boj 4196
 * Usage: build graph only with add_edge. use C.find_scc();
 */

struct Cosaraju
{
    using graph = vector<vector<int>>;
    int V, E;
    graph G, rG;
    vector<vector<int>> scc;
    vector <int> dfs_stack, scc_id;
    vector <bool> visit;
    Cosaraju(int n = 0) {
        re_init(n);
    }
    void re_init(int n) {
        V = n;
        G.clear(); rG.clear(); visit.clear(); scc.clear();
        G.resize(V+5); rG.resize(V+5);
        visit.resize(V+5, 0); scc.resize(V+5);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    void dfs(int r) {
        visit[r] = true;
        for (auto it:G[r])
            if (!visit[it])
                dfs(it);
        dfs_stack.push_back(r);
    }

    void rev_dfs(int r, int scc_num) {
        visit[r] = true;
        scc[scc_num].push_back(r);
        for (auto it:rG[r])
            if (!visit[it])
                rev_dfs(it, scc_num);
    }

    void find_scc() {
        fill(all(visit),0);

        for (int i = 1; i<=V; i++)
            if (!visit[i])
                dfs(i);

        fill(all(visit),0);
        int scc_count = 0;

        while(!dfs_stack.empty()) {
            int tp = dfs_stack.back();
            dfs_stack.pop_back();
            if (!visit[tp]) {
                rev_dfs(tp, scc_count);
                scc_count++;
            }
        }

        scc.resize(scc_count);
        scc_id.clear(); scc_id.resize(V+5);
        fill(all(scc_id),0);
        for (int i = 0; i<scc.size(); i++)
            for (auto itt:scc[i])
                scc_id[itt] = i;


    }

    vector <int> find_scc_indeg() {
        vector <int> indeg;
        indeg.resize(scc.size(), 0);
        for (int i = 1; i<=V; i++)
            for (auto it:G[i])
                if (scc_id[it]!=scc_id[i])
                    indeg[scc_id[it]]++;
        return indeg;
    }
};
