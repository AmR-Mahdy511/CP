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
const int Mod = 1e9 + 7 , Max = 1e7 + 5;
vector < ll > spf( Max , 0 ) , primes;
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
// calc Euler's Totient Function / Phi Function
ll phi( ll n )
{
    ll res = n;
    while( n > 1 )
    {
        ll temp = spf[n];
        while( n % temp == 0 ) n /= temp;
        res -= ( res / temp );
    }
    return res;
}
// Calc spf and phi and get primes together
const int Max = 5e6 + 5;
vector < int > spf( Max + 5) , primes;
vector < ull > phi( Max + 5 , 0 );
void calc_spf()
{
    phi[1] = 1;
    for(int i = 2; i < Max; i++)
    {
        if(spf[i] == 0)
        {
            spf[i] = i;
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for(int p : primes)
        {
            if(p > spf[i] || 1LL * i * p >= Max) break;
            spf[i * p] = p;
            if( i % p == 0 )
                phi[i * p] = phi[i] * p;
            else
                phi[i * p] = phi[i] * (p - 1);
        }
    }
    // vector<int>().swap(spf); optimize for better memory
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

ll modinv(ll a) {
    return powmod(a, Mod - 2, Mod);
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
// get the number of divisors for n
int number_of_divisors(ll n){
    int divisors = 0;
    for(int i = 1; i < sqrt(n); i++) if(n % i == 0) divisors += 2;
    return divisors + (sqrt(n) == (int)sqrt(n));
}

// get Summation of divisors for n
ll sum_of_divisors(ll n){
    ll sum_divisors = 0;
    for(int i = 1; i < sqrt(n); i++) if(n % i == 0) sum_divisors += ((n / i) + i);
    ll sq = sqrt(n);
    return sum_divisors + (sq * sq == n ? sq : 0);
}
// sum of divisor of number in range [1 ... n]
 ll divisorSum(ll num){
    ll sum = 0;
    for (ll i = 1; i <= sqrt(num); i++) {
        ll t1 = i * (num / i - i + 1);
        ll t2 = (((num / i) * (num / i + 1)) / 2) - ((i * (i + 1)) / 2);
        sum += t1 + t2;
        }
        return sum;
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
