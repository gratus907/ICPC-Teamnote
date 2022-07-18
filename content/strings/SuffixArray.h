/**
 * Source: http://www.secmem.org/blog/2021/07/18/suffix-array-and-lcp/
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: BOJ 9248
 */

struct SuffixArray {
    vector <int> buildSA(string &s) {
        int n = s.length(), m = max(256, n) + 1;
        vector <int> sa(n), rank(n*2), new_rank(n*2), cnt(m), idx(n);
        for (int i = 0; i < n; i++) {
            rank[i] = s[i]; sa[i] = i;
        }
        for (int d = 1; d < n; d = d * 2) {
            auto cmp = [&](int i,int j){
                return rank[i] < rank[j] || (rank[i]==rank[j] && rank[i+d]<rank[j+d]);};
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) cnt[rank[i+d]]++;
            for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--) idx[--cnt[rank[i+d]]] = i;
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++) cnt[rank[i]]++;
            for (int i = 1; i < m; i++) cnt[i] += cnt[i-1];
            for (int i = n-1; i >= 0; i--) sa[--cnt[rank[idx[i]]]] = idx[i];
            new_rank[sa[0]] = 1;
            for (int i = 1; i < n; i++) new_rank[sa[i]] = new_rank[sa[i-1]] + cmp(sa[i-1], sa[i]);
            rank = new_rank;
            if (rank[sa[n-1]] == n) break;
        }
        return sa;
    }

    vector <int> buildLCP(string &s, vector<int> &sa) {
        int n = s.length();
        vector <int> lcp(n), isa(n);
        for (int i = 0; i < n; i++) isa[sa[i]] = i;
        for (int k = 0, i = 0; i < n; i++) {
            if (!isa[i]) continue;
            for(int j = sa[isa[i]-1]; s[i+k]==s[j+k]; k++);
            lcp[isa[i]] = (k ? k-- : 0);
        }
        return lcp;
    }
};

