struct DSU
{
    int par[V], sz[V];
    DSU(){init(V);}
    void init(int n)
    {
        for (int i = 0; i<n; i++)
        par[i] = i, sz[i] = 1;
    }
    int find(int x)
    {
        return x == par[x] ? x : (par[x] = find(par[x]));
    }
    int getSize(int k){return sz[find(k)];}
    void unite(int x, int y)
    {
        int u=find(x), v=find(y);
        if(u==v) return;
        if(sz[u]>sz[v]) swap(u, v);
        sz[v]+=sz[u];
        sz[u] = 0;
        par[u] = par[v];
    }
};
