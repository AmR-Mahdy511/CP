ll Extended_Euclidean( ll a , ll b , ll &x , ll &y )
{
    if( b == 0 )
    {
        x = 1;
        y = 0;
        return a;
    }
    ll go = Extended_Euclidean( b  , a % b , y , x);
    y -= ( a / b ) * x;
    return go;
}
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

ll modinv(ll a , ll Mod ) {
    return powmod(a, Mod - 2, Mod);
}

// Chinese Remainder Theorem , works only if all m[i] are prime (pairwise coprime)
// returns {-1,-1} if no solution exists
pair < ll , ll > CRT( vector < ll > &v , vector < ll > &m )
{
    if( v.size() != m.size() ) return {-1,-1};
    int n = v.size();
    ll all_m = 1 , ans = 0;
    for(int i = 0 ; i < n ; i++) all_m *= m[i];
    for(int i = 0 ; i < n ; i++)
    {
        ll Ai = v[i] , cur_m = all_m / m[i];
        ll inv = modinv( ( cur_m % m[i] ) , m[i] );
        ans = ( ans + ( Ai % m[i]) * ( ( cur_m % all_m ) % all_m ) * inv ) % all_m;
    }
    while( ans < 0 ) ans += all_m;
    return { ans , all_m };
    // ans + k * All such that k any int is a valid solution
}

// Chinese Remainder Theorem , works for any m[i] (prime or not, coprime or not)
// returns {-1,-1} if no solution exists
// Chinese Remainder Theorem , works for any m[i] (prime or not, coprime or not)
// returns {-1,-1} if no solution exists
pair < ll , ll > CRT_general( vector < ll > &v , vector < ll > &m )
{
    if( v.size() != m.size() ) return {-1,-1};
    int n = v.size();
    ll ans = v[0] , all_m = m[0];
    for(int i = 1 ; i < n ; i++)
    {
        ll Ai = v[i] , cur_m = m[i];
        ll p , q;
        ll g = Extended_Euclidean( all_m , cur_m , p , q );

        if( (Ai - ans) % g != 0 ) return {-1,-1};

        ll lcm = all_m / g * cur_m;
        ll diff = (Ai - ans) / g;
        ans = ans + all_m * ( (diff % (cur_m/g)) * p % (cur_m/g) );
        ans %= lcm;
        if( ans < 0 ) ans += lcm;

        all_m = lcm;
    }
    return { ans , all_m };
    // ans + k * all_m such that k any int is a valid solution
}
