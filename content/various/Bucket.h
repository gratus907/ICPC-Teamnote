/**
 * Author: Gratus907
 * Date: 2023-07-21
 * License: CC0
 * Description: Be careful and double check for off by 1 error
 * Status: tested
 */

struct bset {
    // bitset is a size-64 bucket
    bitset<64> arr[1577];
    bset() {}
    // single-query
    inline int bitquery(int idx) {
        return arr[idx >> 6][idx&63]?1:0;
    }
    // single-operation
    inline void bitflip(int idx) {
        arr[idx >> 6][idx & 63].flip();
    }
    void flip(int l, int r) {
        if (r - l < 200) {
            for (int i = l; i <= r; i++)
                bitflip(i);
            return;
        }
        int u = l >> 6;
        int v = r >> 6;
        for (int i = u+1; i < v; i++) {
            // bucket-operation
            arr[i].flip();
        }
        for (int i = l; i < ((u+1) << 6); i++) bitflip(i);
        for (int i = (v << 6); i <= r; i++) bitflip(i);
    }
    int query(int l, int r) {
        int ans = 0;
        if (r - l < 200) {
            for (int i = l; i <= r; i++)
                ans += bitquery(i);
            return ans;
        }
        int u = l >> 6;
        int v = r >> 6;
        for (int i = u+1; i < v; i++) {
            // bucket-query
            ans += arr[i].count();
        }
        for (int i = l; i < ((u+1) << 6); i++) ans += bitquery(i);
        for (int i = (v << 6); i <= r; i++) ans += bitquery(i);
        return ans;
    }
};