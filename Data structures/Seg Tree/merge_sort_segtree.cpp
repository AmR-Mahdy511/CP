ll oo = 1e16;

struct Node
{
    vector < int > val;
};

template < typename T >
struct SegmentTree
{

private:
    vector< T > seg;
    int sz;
    T skip;

        T merge(T a, T b)
        {
            T res;
            int i = 0, j = 0;

            while(i < a.val.size() && j < b.val.size())
            {
                if(a.val[i] < b.val[j]) res.val.push_back(a.val[i++]);
                else res.val.push_back(b.val[j++]);
            }

            while(i < a.val.size())
            res.val.push_back(a.val[i++]);

            while(j < b.val.size())
            res.val.push_back(b.val[j++]);

            return res;
        }

    ll greater( vector < int > &v , ll k )
    {
        ll l = 0 , r = v.size() - 1 , ans = v.size();
        while( l <= r )
        {
            ll mid = l + ( r- l ) / 2;
            if( v[mid] > k ) ans = mid , r = mid - 1;
            else l = mid + 1;
        }
        return v.size() - ans;
    }
    ll smaller( vector < int > &v , ll k )
    {
        ll l = 0 , r = v.size() - 1 , ans = v.size();
        while( l <= r )
        {
            ll mid = l + ( r- l ) / 2;
            if( v[mid] >= k ) ans = mid , r = mid - 1;
            else l = mid + 1;
        }
        return ans;        
    }
    void build( int l , int r , int node , vector< T >& v )
    {
        if( l == r )
        {
            if( l < v.size() ) seg[ node ] = v[l];
            return;
        }
        ll mid = l + ( r - l ) / 2;
        build( l , mid , 2*node+1 , v );
        build( mid+1 , r , 2*node+2 , v );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }

    void update( int l , int r , int node , int idx , T val )
    {
        if( l == r )
        {
            seg[ node ] = val ;
            return;
        }
        ll mid = l + ( r - l ) / 2;
        if( idx <= mid ) update( l , mid , 2*node+1 , idx , val );
        else update( mid+1 , r , 2*node+2 , idx , val );
        seg[ node ] = merge( seg[ 2*node+1 ] , seg[ 2*node+2 ] );
    }

    ll query(int l, int r, ll k, int node, int lx, int rx)
    {
        if( l > rx || r < lx ) return 0;
        if( l >= lx && r <= rx ) return smaller( seg[ node ].val , k );
        ll mid = l + ( r - l ) / 2;
        return (query( l , mid , k , 2*node+1 , lx , rx ) + query( mid+1 , r , k , 2*node+2 , lx , rx ));
    }

    ll queryGreater(int l, int r, ll k, int node, int lx, int rx)
    {
        if( l > rx || r < lx ) return 0;
        if( l >= lx && r <= rx ) return greater( seg[ node ].val , k );
        ll mid = l + ( r - l ) / 2;
        return (queryGreater( l , mid , k , 2*node+1 , lx , rx ) + queryGreater( mid+1 , r , k , 2*node+2 , lx , rx ));
    }

public:
    SegmentTree( int n , vector< T >& v )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        seg.assign( sz << 1 , skip );
        build( 0 , sz-1 , 0 , v );
    }
    SegmentTree( int n )
    {
        sz = 1;
        while( sz < n ) sz <<= 1;
        skip = T();
        seg.assign( sz << 1 , skip );
    }
    void update( int idx , T val )
    {
        update( 0 , sz-1 , 0 , idx , val );
    }

    ll query(int l , int r , ll k)
    {
        return query(0 , sz-1 , k , 0 , l , r);
    }

    ll queryGreater(int l , int r , ll k)
    {
        return queryGreater(0 , sz-1 , k , 0 , l , r);
    }

};