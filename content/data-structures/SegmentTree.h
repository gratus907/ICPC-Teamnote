/**
 * Author: Gratus907
 * Date: 2020-10-08
 * License: CC0
 * Source: folklore
 * Description: Point modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct segtree {
    using elem = int;
    int n;
    elem T[2*N];

    inline elem agg(elem a, elem b) {
        return max(a, b);
    }

    void build(vector<elem> &v) {
        n = v.size();
        for (int i = 0; i<n; i++)
            T[n+i] = v[i];
        for (int i = n-1; i>0; i--)
            T[i] = agg(T[i<<1], T[(i<<1)|1]);
    }
    void modify(int pos, elem val) {
        for (T[pos += n] = val; pos > 1; pos >>= 1)
            T[pos >> 1] = agg(T[pos], T[pos^1]);
    }
    // query is on [l, r)!!
    elem query(int l, int r){
        elem res = 0;
        for (l += n, r += n; l < r; l >>=1, r>>=1) {
            if (l & 1) res = agg(T[l++], res);
            if (r & 1) res = agg(res, T[--r]);
        }
        return res;
    }
};