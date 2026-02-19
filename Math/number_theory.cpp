const int Mod = 1e9 + 7 , Max = 1e7 + 5;
// calc smallest prime factor
vector < ll > spf( Max , 0 );
void calc_spf()
{
    for(int i = 2 ; i < Max ; i++)
    {
        if(!spf[i])
        {
            for( int j = i ; j < Max ; j += i ) if(!spf[j]) spf[j] = i;
        }
    }
}
// calc smallest prime factor in better time ( linear sieve )
void calc_spf()
{
    for(int i = 2; i < Max; i++)
    {
        if(spf[i] == 0)
        {
            spf[i] = i;
            primes.push_back(i);
        }

        for(int p : primes)
        {
            if(p > spf[i] || 1LL * i * p >= Max) break;
            spf[i * p] = p;
        }
    }
}
// power mod
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
// prime factors of number
vector< pair<ll,ll> > primeFactorze(ll n)
{
    vector< pair<ll,ll> > v;
    for(ll i = 2 ; i*i <=n ;i++ )
    {
        int count = 0;
        while(n%i==0)
        {
            count++;
            n /= i;
        }
        if( count ) v.push_back({i,count});
    }
    if( n > 1 ) v.push_back({n,1});
    return v;
}
// get divisors of number
vector< ll > divisors( ll n )
{
    vector< ll > v;
    for ( ll i = 1; i * i <= n; i++ )
    {
        if (n % i == 0)
        {
            v.push_back(i);
            if ( i * i != n )
            {
                v.push_back(n / i);
            }
        }
    }
    return v;
}
// sieve
vector< bool > isPrime( Max, 1 );
void sieve()
{
    isPrime[0] = 0; isPrime[1] = 0;
    for(ll i = 2; i*i < Max ;i++)
    {
        if(isPrime[i])
        {
            for( ll j=i*i ;j < Max ;j+=i )
            {
                isPrime[j] = 0;
            }
        }
    }
}
// linear sieve
vector< bool > isPrime( Max ,1 );vector< int >primes;
void linearSieve()
{
    isPrime[0]=isPrime[1]=0;
    for( ll i = 2;i < Max;i++ )
    {
        if(isPrime[i]) primes.push_back(i);
        for(auto it:primes)
        {
            if( i*it>= Max ) break;
            isPrime[i*it] = 0;
            if(i%it==0) break;
        }
    }
}
// + * - / wit Mod
const int Mod = 1e9 + 7
ll add(ll a,ll b)
{
    return ( (a%Mod) + (b%Mod) )%Mod;
}
ll mul(ll a,ll b)
{
    return ( (a%Mod) *(b%Mod) )%Mod;
}
ll sub(ll a,ll b)
{
    return ((( (a%Mod) -(b%Mod) ) %Mod ) +Mod ) %Mod;
}
ll divide(ll a,ll b)
{
    return mul( a ,powmod(b,Mod-2) );
}
