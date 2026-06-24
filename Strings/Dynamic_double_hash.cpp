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
const int Mod1 = 1e9 + 7, Mod2 = 1e9 + 9 ;
int Base1 = rand( 31 , 1e9 ), Base2 = rand( 31 , 1e9 ) ;
struct Node
{
    ll Hash1 , Hash2 ;
};

template < typename T >
struct Dynamic_double_hash
{
private:
    vector< T > seg;
    int sz;
    vector < ll > pw1{1} , invpw1{1} ;
    vector < ll > pw2{1} , invpw2{1} ;
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
    void precalc( int n )
    {
        ll inv1 = powmod( Base1 , Mod1 - 2 , Mod1 );
        ll inv2 = powmod( Base2 , Mod2 - 2 , Mod2 ); 
        while( pw1.size() <= n )
        {
            ll last_pw1 = pw1.back() , last_invpw1 = invpw1.back() ;
            pw1.push_back( ( last_pw1 * Base1 ) % Mod1 );
            invpw1.push_back( ( last_invpw1 * inv1 ) % Mod1 );
    
            ll last_pw2 = pw2.back() , last_invpw2 = invpw2.back();
            pw2.push_back( ( last_pw2 * Base2 ) % Mod2 );
            invpw2.push_back( ( last_invpw2 * inv2 ) % Mod2 );     
        }
    }
    T merge( T a , T b )
    {
        Node res;
        res.Hash1 = ( a.Hash1 + b.Hash1 ) % Mod1;
        res.Hash2 = ( a.Hash2 + b.Hash2 ) % Mod2;
        return res;
    }
 
    void build( int l , int r , int node , const string &s )
    {
        if( l == r )
        {
            if( l < s.size() )
            {
                ll Val = s[l] - 'a' + 1;
                seg[node] = { Val * pw1[l] % Mod1 , Val * pw2[l] % Mod2 };
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
            seg[node] = { Val * pw1[idx] % Mod1 , Val * pw2[idx] % Mod2 };
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
 
public:
    Dynamic_double_hash( int n , const string &s )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        // skip = T();
        skip = Node{ 0 , 0 } ;
        precalc(n);
        seg.assign( sz << 1 , skip );
        build( 0 , sz-1 , 0 , s );
    }
    Dynamic_double_hash( int n )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        skip = Node{ 0 , 0 } ;
        precalc(n);
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
    pair < ll , ll > get( int l , int r )
    {
        Node cur = query(l , r);
        ll h1 = cur.Hash1 * invpw1[l] % Mod1;
        ll h2 = cur.Hash2 * invpw2[l] % Mod2;
        while(h1 < 0) h1 += Mod1;
        while(h2 < 0) h2 += Mod2;
        return { h1 , h2 };
    }
};

void solve() {
    int n , m;
    cin >> n >> m;
    string s; cin >> s;
    Dynamic_double_hash < Node > dh1( n , s );
    string temp = s;
    reverse(all(temp));
    Dynamic_double_hash < Node > dh2( n , temp );
    for(int i = 0 ; i < m ; i++)
    {
        int op; cin >> op;
        if( op == 1 )
        {
            int idx;
            char ch;
            cin >> idx >> ch;
            idx--;
            dh1.update( idx , ch);
            int new_idx = n - idx - 1;
            dh2.update( new_idx , ch );
        }
        else
        {
            int l , r;
            cin >> l >> r;
            l--; r--;
            pair < int , int > p1 = dh1.get(l,r);
            int new_l = n - r - 1 , new_r = n - l - 1 ;
            pair < int , int > p2 = dh2.get(new_l,new_r);
            if( p1 == p2 ) cout << "YES" << nl;
            else cout << "NO" << nl;
        }
    }
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
