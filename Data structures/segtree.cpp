template < typename T >
struct SegmentTree
{
private:
    vector< T > seg;
    int sz;
    T skip;
 
    T merge( T a , T b )
    {
        return min(a,b);
    }
 
    void build( int l , int r , int node , vector< T >& v )
    {
        if( l == r )
        {
            if( l < v.size() )  seg[ node ] = v[ l ];
            return;
        }
        int mid = l + ( r - l ) / 2;
        build( l , mid , 2*node+1 , v );
        build( mid+1 , r , 2*node+2 , v );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }
 
    void update( int l , int r , int node , int idx , T val )
    {
        if( l == r )
        {
            seg[ node ] = val;
            return;
        }
        ll mid = l + ( r - l ) / 2;
        if( idx <= mid ) update( l , mid , 2*node+1 , idx , val );
        else update( mid+1 , r , 2*node+2 , idx , val );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }
 
    T query( int l , int r , int node , int lx , int rx )
    {
        if( l > rx || r < lx ) return skip;
        if( l >= lx && r <= rx ) return seg[ node ];
        ll mid = l + ( r - l ) / 2;
        return merge( query( l , mid , 2*node+1 , lx , rx ) , query( mid+1 , r , 2*node+2 , lx , rx ) );
    }
 
public:
    SegmentTree( int n , vector< T >& v )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        skip = 1e15;
        seg.assign( sz << 1 , skip );
        build( 0 , sz-1 , 0 , v );
    }
 
    void update( int idx , T val )
    {
        update( 0 , sz-1 , 0 , idx , val );
    }
 
    T query( int l , int r )
    {
        return query( 0 , sz-1 , 0 , l , r );
    }
};
