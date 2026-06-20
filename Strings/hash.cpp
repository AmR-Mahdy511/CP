mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() ) ;
int rand( int l, int r )
{
    return uniform_int_distribution<int>( l, r )( rng ) ;
}
// dont forget this and this struct is ( zero based )
// const int Mod = 1e9 + 7, Mod2 = 1e9 + 9 ;
// const int Base = rand( 31 , 1e9 ), Base2 = rand( 31 , 1e9 ) ;
struct shash
{
    int base , Mod , inv , n;
    vector < ll > pw{1} , invpw{1} , pref{0};

    shash(){};
    shash( const string &s , int m , int b )
    {
        Mod = m;
        base = b;
        inv = 1;
        n = s.size();
        // to get inv 
        ll cur = base;
        int e = Mod - 2;
        while( e )
        {
            if( e & 1 ) inv = ( inv * cur ) % Mod;
            cur = ( cur * cur ) % Mod;
            e >>= 1 ;
        }
        // build hash prefix
        for(int i = 0 ; i < n ; i++)
        {
            ll last_pw = pw.back() , last_invpw = invpw.back() , last_prefix = pref.back() , last_ch = s[i] - 'a' + 1;
            pw.push_back( ( last_pw * base ) % Mod );
            invpw.push_back( ( last_invpw * inv ) % Mod );
            pref.push_back(( last_prefix + ( last_ch * pw[i]) ) % Mod );
        }
    }
    int get( int l , int r )
    {
        if( l == 0 ) return pref[ r + 1 ];
        return( ( ( pref[ r + 1 ] - pref[ l ] + Mod ) % Mod ) * invpw[l] )% Mod;
    }
};
