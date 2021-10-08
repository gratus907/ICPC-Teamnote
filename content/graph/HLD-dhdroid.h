/**
 * Author: DHDroid
 * Description: HeavyLight Decomposition. 
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

struct query {
    int x, y, c;
};

struct SEGTREE {
    int* tree;
    int size;
    SEGTREE(int N) {
        tree = new int[6*N];
        for(int i=0; i<6*N; i++) {
            tree[i] = 0;
        }
        size = N;
    }
    int update(int i, int v, int l, int r, int node) {
        if(i < l || i > r) {
            return tree[node];
        }
        else {
            if(l==r) {
                return tree[node]=tree[node]+v;
            }
            int mid = (l+r)>>1;
            return tree[node] = update(i, v, l, mid, 2*node) + update(i, v, mid+1, r, 2*node+1);
        }
    }
    int query(int s, int e, int l, int r, int node) {
        if(e<l || s>r) {
            return 0;
        }
        if(s<=l && e>=r) {
            return tree[node];
        }
        else {
            int mid = (l+r)>>1;
            return query(s, e, l, mid, 2*node) + query(s, e, mid+1, r, 2*node+1);
        }
    }
};

vector<int> lis[100020];
int sz[100020]; // size of subtree
int depth[100020];

int A[100020]; // sum of children
int B[100020]; // maximum value

vector<SEGTREE> segA;
vector<SEGTREE> segB;


vector<int> chain[100020];
int chain_num[100020], chain_idx[100020], chain_size[100020];

void HLD(int i, int cur_chain) {
    chain_num[i] = cur_chain;
    chain_idx[i] = chain_size[cur_chain];
    chain[cur_chain].push_back(i);
    chain_size[cur_chain]++;

    int tmp = -1;
    for(auto j: lis[i]) {
        if(depth[j] > depth[i] && (tmp == -1 || sz[j] > sz[tmp])) {
            tmp = j;
        }
    }
    if(tmp != -1) {
        HLD(tmp, cur_chain);
    }
    for(auto j: lis[i]) {
        if(depth[j] > depth[i] && j != tmp) {
            HLD(j, j);
        }
    }
}

void init_seg(int N) {
    for(int i=0; i<=N; i++) {
        int szs = chain_size[i];
        segA.emplace_back(SEGTREE(szs));
        segB.emplace_back(SEGTREE(szs));
    }
}