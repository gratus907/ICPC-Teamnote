const int N = 1001010;
struct Segtree
{
    int n, h;
    int T[2*N];
    int Lazy[N];
    int32_t Len[2*N];
    void apply(int pos, int val)
    {
        T[pos] += val * Len[pos];
        if (pos < n) Lazy[pos] += val;
    }
    void build(vector<int> &v)
    {
        n = v.size();
        h = sizeof(int) * 8 - __builtin_clz(n);
        for (int i = 0; i<n; i++)
        {
            T[n+i] = v[i];
            Len[n+i] = 1;
        }
        for (int i = n-1; i>0; i--)
        {
            T[i] = T[i<<1] + T[(i<<1)|1];
            Len[i] = Len[i<<1] + Len[(i<<1)|1];
        }
    }
    void pupd(int p)
    {
        while(p > 1)
        {
            p>>=1;
            T[p] = (T[p<<1] + T[(p<<1)|1] + (Lazy[p] * Len[p]));
        }
    }
    void propagate(int p)
    {
        for (int s = h; s > 0; s--)
        {
            int i = p >> s;
            if (!i) continue;
            if (Lazy[i] != 0)
            {
                apply(i << 1, Lazy[i]);
                apply((i << 1)|1, Lazy[i]);
                Lazy[i] = 0;
            }
        }
    }
    void modify(int pos, int val)
    {
        for (T[pos += n] = val; pos > 1; pos >>= 1)
            T[pos >> 1] = T[pos] + T[pos^1];
    }
    void modifyRange(int l, int r, int val)
    {
        l += n, r += n;
        int l0 = l, r0 = r;
        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }
        pupd(l0), pupd(r0-1);
    }
    // query is on [l, r)!!
    int query(int l, int r)
    {
        l += n, r += n;
        propagate(l); propagate(r-1);
        int res = 0;
        for (; l < r; l >>=1, r>>=1)
        {
            if (l & 1)
                res += T[l++];
            if (r & 1)
                res += T[--r];
        }
        return res;
    }
} S;
