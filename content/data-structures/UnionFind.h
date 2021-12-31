/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct DSU
{
    int par[V], sz[V];
    DSU(){init(V);}
    void init(int n) {
        for (int i = 0; i<n; i++)
        par[i] = i, sz[i] = 1;
    }
    int find(int x) {
        return x == par[x] ? x : (par[x] = find(par[x]));
    }
    bool unite(int x, int y) {
        int u=find(x), v=find(y);
        if(u==v) return false;
        if(sz[u]>sz[v]) swap(u, v);
        sz[v]+=sz[u];
        sz[u] = 0;
        par[u] = par[v];
        return true;
    }
};
