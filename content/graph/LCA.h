/**
 * Author: Gratus907
 * Description: LCA in $O(N \log N + Q \log N)$
 */

int n, k;
bool visited[101010];
int par[101010][21], maxedge[101010][21], minedge[101010][21];
int d[101010];
vector <pii> graph[101010]; // {destination, weight}
void dfs(int here, int depth) { // run dfs(root,0)
    visited[here] = true;
    d[here] = depth;
    for (auto there: graph[here]) {
        if (visited[there.first])
            continue;
        dfs(there.first, depth + 1);
        par[there.first][0] = here;
        maxedge[there.first][0] = there.second;
        minedge[there.first][0] = there.second;
    }
}

void precomputation() {
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
            maxedge[j][i] = max(maxedge[j][i - 1],
                                maxedge[par[j][i - 1]][i - 1]);
            minedge[j][i] = min(minedge[j][i - 1],
                                minedge[par[j][i - 1]][i - 1]);
        }
    }
}

pii lca(int x, int y) {
    int maxlen = INT_MIN;
    int minlen = INT_MAX;
    if (d[x] > d[y])
        swap(x, y);
    for (int i = 20; i >= 0; i--) {
        if (d[y] - d[x] >= (1 << i)) {
            minlen = min(minlen, minedge[y][i]);
            maxlen = max(maxlen, maxedge[y][i]);
            y = par[y][i];
        }
    }
    if (x == y)
        return {minlen, maxlen};
    // x is lca point
    for (int i = 20; i >= 0; i--) {
        if (par[x][i] != par[y][i]) {
            minlen = min(minlen, min(minedge[x][i], minedge[y][i]));
            maxlen = max(maxlen, max(maxedge[x][i], maxedge[y][i]));
            x = par[x][i];
            y = par[y][i];
        }
    }
    minlen = min(minlen, min(minedge[x][0], minedge[y][0]));
    maxlen = max(maxlen, max(maxedge[x][0], maxedge[y][0]));

    int lca_point = par[x][0];
    return {minlen, maxlen};
    // lca_point is lca point
}

void lca_construction() {
    dfs(1, 0);
    precomputation();
}