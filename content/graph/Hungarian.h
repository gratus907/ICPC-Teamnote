/**
 * Author: Jeonggyun (Secmem)
 * Date: 
 * License: CC0
 * Source: Secmem
 * Description: Min-cost matching on bipartite graphs, in $O(n^3)$ time.
 * Status: stress-tested
 */

int w[N][N];
int match_x[N];
int match_y[N];

int l_x[N], l_y[N];
bool s[N], t[N];
int slack[N];
int slack_x[N];

int tree_x[N];
int tree_y[N];

int hungarian(int n) {
	memset(match_x, -1, sizeof(match_x));
	memset(match_y, -1, sizeof(match_y));
	int ret = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			l_x[i] = max(l_x[i], w[i][j]);
		}
	}
	memset(l_y, 0, sizeof(l_y));

	int m = 0;
	while (m != n) { // repeat at most V times
		memset(tree_x, -1, sizeof(tree_x));
		memset(tree_y, -1, sizeof(tree_y));
		memset(s, 0, sizeof(s));
		memset(t, 0, sizeof(t));

		int s_start;
		for (int i = 0; i < n; ++i) { // O(V)
			if (match_x[i] == -1) {
				s[i] = 1;
				s_start = i;
				break;
			}
		}

		for (int i = 0; i < n; ++i) { // init slack
			slack[i] = l_x[s_start] + l_y[i] - w[s_start][i];
			slack_x[i] = s_start;
		}

		here:
		int y = -1;
		for (int i = 0; i < n; ++i) { // compare: O(V)
			if (slack[i] == 0 && !t[i]) y = i;
		}

		if (y == -1) { // n_l = t
			// update label
			int alpha = INF;
			for (int i = 0; i < n; ++i) { // O(V)
				if (!t[i]) {
					alpha = min(alpha, slack[i]);
				}
			}
			for (int i = 0; i < n; ++i) { // O(V)
				if (s[i]) l_x[i] -= alpha;
				if (t[i]) l_y[i] += alpha;
			}
			for (int i = 0; i < n; ++i) { // O(V)
				if (!t[i]) {
					slack[i] -= alpha;
					if (slack[i] == 0) {
						y = i;
					}
				}
			}
		}

		// n_l != t is guaranteed
		if (match_y[y] == -1) { // free
			tree_y[y] = slack_x[y];
			while (y != -1) {
				int x = tree_y[y];
				match_y[y] = x;
				int next_y = match_x[x];
				match_x[x] = y;
				y = next_y;
			}
			m++;
		}
		else { // matched
			int z = match_y[y];
			tree_x[z] = y;
			tree_y[y] = slack_x[y];
			s[z] = 1;
			t[y] = 1;
            // z is added - update slack and n_l
			for (int i = 0; i < n; ++i) { // O(V)
				if (l_x[z] + l_y[i] - w[z][i] < slack[i]) {
					slack[i] = l_x[z] + l_y[i] - w[z][i];
					slack_x[i] = z;
				}
			}
			goto here;
		}
	}

	for (int i = 0; i < n; ++i) {
		ret += l_x[i];
		ret += l_y[i];
	}
	return ret;
}