/**
 * Author: Jayeon Yi
 * License: CC0
 * Source: 
 * Description: insertion queries come in decreasing v.y/v.x order, queries come in increasing x order.
 */
const int MEM=50003;
struct cht{
    int s=0,e=0,id[MEM];
    pll f[MEM];
    double cross(int a,int b){
        return 1.0*(f[a].y-f[b].y)/(f[b].x-f[a].x);
    }
    void insert(pll v,int l){
        f[e]=v;
        id[e]=l;
        while(s+1<e && cross(e-2,e-1)>cross(e-1,e)){
            f[e-1]=f[e];
            id[e-1]=id[e];
            --e;
        }
        ++e;
    }
    ll query(ll x){
        while(s+1<e && f[s+1].y-f[s].y <= x*(f[s].x-f[s+1].x)) ++s;
        return f[s].x * x + f[s].y;
    }
} CHT;