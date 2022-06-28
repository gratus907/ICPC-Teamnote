
/**
 * Author: stet-stet
 * Date: 2022-06-28
 * License: CC0
 * Source: folklore
 * Description: Point modification, interval sum query on $[l, r)$.
 * Time: O(\log N)
 * Status: tested(1) - Q2042.
 */

#include<functional>
#include<vector>
//#include<iostream>
using std::vector;
using namespace std;

constexpr size_t powerOfTwoGreaterOrEqualTo(size_t N){
    N--;
    size_t ret=0;
    while(N!=0){
        N/=2; ++ret;
    }
    return 1<<ret;
}

template<size_t N, typename elem, typename Reducer>
class CanonicalSegtree
{
    // data indices are of type size_t
    // each datum is of type elem
    // Reducer is the class of reducing function, this allows us to receive everything as args 
    // ( it's also alledgedly much faster than stuff like function<int(int,int)> )

    // 0628: abandoned arrays: arrays cause stack overfloew

    vector<elem> T;
    const size_t arraysize = powerOfTwoGreaterOrEqualTo(N);
    Reducer reducer;

    public:
    CanonicalSegtree(Reducer _reducer)
        : T(2*powerOfTwoGreaterOrEqualTo(N)), reducer{_reducer}
    { }
    CanonicalSegtree(Reducer _reducer, const vector<elem>& v)
        : T(2*powerOfTwoGreaterOrEqualTo(N)), reducer{_reducer}
    {
        build(v);    
    }

    void build(const vector<elem> &v) {
        for (size_t i = 0; i< v.size(); i++)
            T[arraysize+i] = v[i];
        for (size_t i = arraysize-1; i>0; i--)
            T[i] = reducer(T[i<<1], T[(i<<1)|1]);
    }
    void modify(size_t pos, elem val) {
        for (T[pos += arraysize] = val; pos > 1; pos >>= 1)
            T[pos >> 1] = reducer(T[pos], T[pos^1]);
    }

    // query is on [l, r)!!
    elem query(size_t l, size_t r){
        elem res = 0;
        for (l += arraysize, r += arraysize; l < r; l >>=1, r>>=1) {
            if (l & 1) res = reducer(T[l++], res);
            if (r & 1) res = reducer(res, T[--r]);
        }
        return res;
    }
};

template<size_t N, typename elem, typename Reducer>
auto makeSegTree(const Reducer& reducer){
    return CanonicalSegtree<N,elem,Reducer>(reducer);
}

template<size_t N, typename elem=int> // default will be int, unless otherwise noted.
auto makeSumSegTree(){
    auto _reducer = [](elem x,elem y){return x+y;};
    return makeSegTree<N,elem>(_reducer);
}

// // TEST: BOJ 2042
// int main(){ 
//     cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
//     int n,m,k;
//     cin >> n >> m >> k;
//     vector<__int128> a (n);
//     for(int i=0;i<n;++i){
//     	long long aaa;
//         cin >> aaa;
//     	a[i] = aaa;
//     }
//     //__int128 zero=0ll;
//     auto tree = makeSumSegTree<1000000, __int128>();
//     tree.build(a);
//     for(int i=0;i<m+k;++i){
//         int a;
//         size_t b;
//         long long int c;
//         cin >> a>>b>>c;
//         if(a==1) tree.modify(b-1,c);
//         else{
// 	        __int128 ans = tree.query(b-1,c);
//             cout << (long long int) ans << '\n';
//         }
//     }
// }