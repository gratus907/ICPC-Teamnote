/**
 * Description: JusticeHui implementation of Centroid Decomposition
 */
int sz[101010]; // subtree size
vector<int> g[101010]; // adj list
int getSize(int v, int b = -1){ // get sz
    sz[v] = 1;
    for(auto i : g[v]) if(i != b) sz[v] += getSize(i, v);
    return sz[v];
}
int getCent(int v, int b = -1, int cap = n){ // find centroid
    for(auto i : g[v]) if(&& i != b && sz[i]*2 > cap) return getCent(i, v, cap);
    return v;
}
