/**
 * Author: Folklore
 * License: CC0
 * Source: 
 * Description: Monotone Deque-DP for sliding-window like query.
 */
dq.push_back({-1, 0});
for (int i = 0; i < n; i++) {
    while (!dq.empty() and dq.front().first < i - d) {
        dq.pop_front();
    }
    dp[i] = max(arr[i], dq.front().second + arr[i]);
    while (!dq.empty() and dq.back().second <= dp[i]) {
        dq.pop_back();
    }
    dq.push_back({i, dp[i]});
    ans = max(ans, dp[i]);
}