ll oo = 1e16;
struct Node
{
    ll sum;
};
 
template < typename T >
struct Lazy_SegmentTree
{
 
private:
    vector< T > seg , lazy;
    int sz;
    T skip;
 
    T merge( T a , T b )
    {
        return ( a + b );
    }
 
    void build( int l , int r , int node , vector< T >& v )
    {
        if( l == r )
        {
            if( l < v.size() ) seg[node] = v[l];
            return;
        }
        ll mid = l + ( r - l ) / 2;
        build( l , mid , 2*node+1 , v );
        build( mid+1 , r , 2*node+2 , v );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }
    void propagate( int node , int l , int r )
    {
        if( lazy[node] == -1 ) return ; // no lazy 
 
        seg[ node ] = lazy[ node ] * ( r - l + 1 );
        if( l != r ) // not a leaf node
        {
            lazy[ 2 * node + 1 ] = lazy[ node ];
            lazy[ 2 * node + 2 ] = lazy[ node ];
        }
        lazy[ node ] = -1;
    }
    void update( int l , int r , int node , int lx , int rx, T val )
    {
        propagate( node , lx , rx );
        if(l > rx or r < lx) return;
        if(l <= lx && r >= rx )
        {
            lazy[ node ] = val;
            propagate( node , lx , rx );
            return;
        }
        ll mid = lx + (rx - lx ) / 2;
        update( l , r , 2 * node + 1 , lx , mid , val);
        update( l , r , 2 * node + 2 , mid + 1 , rx , val);
        seg[ node ] = merge( seg[ 2*node+1 ], seg[ 2*node+2 ]);
    }
 
    // T query(int l, int r, int node, int idx)
    // {
    //     propagate( node , l , r ); 
    //     if( l == r ) return seg[ node ];
    //     ll mid = l + ( r - l ) / 2;
    //     if( idx <= mid ) return query( l , mid , 2 * node + 1 , idx);
    //     else return query( mid + 1 , r , 2 * node + 2 , idx);
    // }
 
    T query(int l, int r, int node, int lx , int rx)
    {
        propagate( node , lx , rx ); 
        if(l > rx || r < lx) return skip;
        if(l <= lx && r >= rx ) return seg[node];
        ll mid = lx + ( rx - lx ) / 2;
        T L = query(l, r, 2*node+1, lx, mid);
        T R = query(l, r, 2*node+2, mid+1, rx);
        return merge(L,R);
    }    
 
public:
    Lazy_SegmentTree( int n , vector< T >& v )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        // skip = oo ;
        seg.assign( sz << 1 , 0 );
        lazy.assign( sz << 1 , -1 );
        build( 0 , sz-1 , 0 , v );
    }
    Lazy_SegmentTree( int n )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        // skip = oo ;
        // skip = 0;
        seg.assign( sz << 1 , 0 );
        lazy.assign( sz << 1 , -1 );
    }
    void update( int l , int r , T val )
    {
        update( l, r, 0, 0, sz - 1, val );
    }
    // T query( int idx)
    // {
    //     return query( 0, sz - 1, 0, idx );
    // }
    T query( int lx , int rx)
    {
        return query( lx, rx, 0, 0, sz - 1 );
    }
};
