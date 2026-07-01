mt19937 rng( chrono::steady_clock::now().time_since_epoch().count() ) ;
int rand( int l, int r )
{
    return uniform_int_distribution<int>( l, r )( rng ) ;
}
// dont forget this and it's ( zero based )
const int Mod = 1e9 + 7, Mod2 = 1e9 + 9 ;
const int Base = rand( 31 , 1e9 ), Base2 = rand( 31 , 1e9 ) ;
struct double_hash
{
    int base1 , Mod1 , inv1 , n;
    int base2 , Mod2 , inv2;
    vector < ll > pw1{1} , invpw1{1} , pref1{0};
    vector < ll > pw2{1} , invpw2{1} , pref2{0};

    double_hash(){};
    double_hash( const string &s , int m1 , int m2 , int b1 , int b2 )
    {
        Mod1 = m1;
        Mod2 = m2;
        base1 = b1;
        base2 = b2;
        inv1 = 1 , inv2 = 1;
        n = s.size();
        // to get first inv 
        ll cur1 = base1;
        int e1 = Mod1 - 2;
        while( e1 )
        {
            if( e1 & 1 ) inv1 = ( inv1 * cur1 ) % Mod1;
            cur1 = ( cur1 * cur1 ) % Mod1;
            e1 >>= 1 ;
        }
        // to get sec inv 
        ll cur2 = base2;
        int e2 = Mod2 - 2;
        while( e2 )
        {
            if( e2 & 1 ) inv2 = ( inv2 * cur2 ) % Mod2;
            cur2 = ( cur2 * cur2 ) % Mod2;
            e2 >>= 1 ;
        }        
        // build hash prefix
        for(int i = 0 ; i < n ; i++)
        {
            ll last_pw1 = pw1.back() , last_invpw1 = invpw1.back() , last_prefix1 = pref1.back() , last_ch1 = s[i] - 'a' + 1;
            pw1.push_back( ( last_pw1 * base1 ) % Mod1 );
            invpw1.push_back( ( last_invpw1 * inv1 ) % Mod1 );
            pref1.push_back(( last_prefix1 + ( last_ch1 * pw1[i]) ) % Mod1 );

            ll last_pw2 = pw2.back() , last_invpw2 = invpw2.back() , last_prefix2 = pref2.back() , last_ch2 = s[i] - 'a' + 1;
            pw2.push_back( ( last_pw2 * base2 ) % Mod2 );
            invpw2.push_back( ( last_invpw2 * inv2 ) % Mod2 );
            pref2.push_back(( last_prefix2 + ( last_ch2 * pw2[i]) ) % Mod2 );            
        }
    }
    pair < ll , ll >  get( int l , int r )
    {
        if( l == 0 )
        {
            return { pref1[ r + 1 ] , pref2[ r + 1 ] };
        }
        else
        {
            ll fi = ( ( ( pref1[ r + 1 ] - pref1[ l ] + Mod1 ) % Mod1 ) * invpw1[l] ) % Mod1;
            ll se = ( ( ( pref2[ r + 1 ] - pref2[ l ] + Mod2 ) % Mod2 ) * invpw2[l] ) % Mod2;
            pair < ll , ll > p = { fi , se };
            return p;            
        }
    }  
};
