int findkth(int node, int l, int r, int target)
{
    if (l == r) return l;
    int lft = segtree[node*2];
    if (lft >= target) return findkth(node*2, l, (l+r)/2, target);
    else return findkth(node*2+1, (l+r)/2+1, r, target-lft);
}
