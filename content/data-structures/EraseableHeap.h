/**
 * Author: rkm ?
 * Date: 2021-07-26
 * Description: Heap with rmv() function.
 * Status: tested scpc 2020
 * Usage: push top pop size and rmv()
 */
struct iHeap {
    static const int inf = 1e9 + 5;
    priority_queue<int> q, qr;
    void rset() { while(!q.empty()) q.pop(); while(!qr.empty()) qr.pop(); }
    inline int size() { return q.size()-qr.size(); }
    inline void rmv(int x) { qr.push(x); }
    inline int top() {
        while(q.size() && qr.size() && q.top() == qr.top()) { q.pop(); qr.pop(); }
        return q.size()?q.top():-inf;
    }
    inline void push(int x) { q.push(x); }
    inline int pop(int x) {int t = top(); rmv(x); return t;}
}