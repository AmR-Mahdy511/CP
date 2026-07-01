#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long 
#define ull unsigned long long
#define ld long double
// #define ld double
#define sp " "
#define nl "\n"
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define popcount  __builtin_popcountll
#define PI 3.14159265358979323846
#define EPS 1e-9

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}
mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() ) ;
int rand( int l, int r )
{
    return uniform_int_distribution<int>( l, r )( rng ) ;
}
// dont forget this and it's ( zero based )
// const int Mod = 1e9 + 7 ;
// int Base = rand( 31 , 1e9 ) ;
struct Node
{
    ll Hash ;
};

template < typename T >
struct Dynamic_single_hash
{
private:
    vector< T > seg;
    int sz;
    vector < ll > pw{1} , invpw{1} ;
    T skip;
    ll powmod(ll x, ll y , ll Mod)
    {
        ll res = 1;
        x = x % Mod;
        if (x == 0) return 0;
        while (y > 0)
        {
            if (y & 1) res = (res*x) % Mod;
            y = y >> 1LL;
            x = (x*x) % Mod;
        }
        return res;
    } 
    void precalc( int n , ll Base , ll Mod )
    {
        ll inv1 = powmod( Base , Mod - 2 , Mod );
        while( pw.size() <= n )
        {
            ll last_pw1 = pw.back() , last_invpw1 = invpw.back() ;
            pw.push_back( ( last_pw1 * Base ) % Mod );
            invpw.push_back( ( last_invpw1 * inv1 ) % Mod );
        }
    }
    T merge( T a , T b )
    {
        Node res;
        res.Hash = ( a.Hash + b.Hash ) % Mod;
        return res;
    }
 
    void build( int l , int r , int node , const string &s )
    {
        if( l == r )
        {
            if( l < s.size() )
            {
                ll Val = s[l] - 'a' + 1;
                seg[node] = { Val * pw[l] % Mod };
            }
            return;
        }
        ll mid = l + ( r - l ) / 2;
        build( l , mid , 2*node+1 , s );
        build( mid+1 , r , 2*node+2 , s );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }
 
    void update( int l , int r , int node , int idx , char c )
    {
        if( l == r )
        {
            ll Val = c - 'a' + 1;
            seg[node] = { Val * pw[idx] % Mod };
            return;
        }
        ll mid = l + ( r - l ) / 2;
        if( idx <= mid ) update( l , mid , 2*node+1 , idx , c );
        else update( mid+1 , r , 2*node+2 , idx , c );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }
 
    T query(int l, int r, int node, int lx, int rx)
    {
        if( l > rx || r < lx ) return skip;
        if( l >= lx && r <= rx ) return seg[ node ];
        ll mid = l + ( r - l ) / 2;
        return merge(query( l , mid , 2*node+1 , lx , rx ) , query( mid+1 , r , 2*node+2 , lx , rx ));
    }

    ll Mod , Base ;

public:
    Dynamic_single_hash( int n , const string &s , ll mod , ll base )
    {
        Mod = mod ; Base = base ;
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = Node{ 0 } ;
        precalc(n , Base , Mod);
        seg.assign( sz << 1 , skip );
        build( 0 , sz-1 , 0 , s );
    }
    Dynamic_single_hash( int n , ll mod , ll base )
    {
        Mod = mod ; Base = base ;
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = Node{ 0 } ;
        precalc(n , Base , Mod);
        seg.assign( sz << 1 , skip );
    }
    void update( int idx , char c )
    {
        update( 0 , sz - 1 , 0 , idx , c );
    }
 
    T query( int l , int r )
    {
        return query( 0 , sz-1 , 0 , l , r );
    }
    ll get( int l , int r )
    {
        Node cur = query(l , r);
        ll h1 = cur.Hash * invpw[l] % Mod;
        while(h1 < 0) h1 += Mod;
        return h1;
    }
};

void solve() {

}

signed main() {
    fast();
    int t = 1;
    // cin >> t;
    for(int i = 1 ; i <= t ; i++) {
        solve();
        // if( i != t ) cout << nl;
    }
    return 0;
}
