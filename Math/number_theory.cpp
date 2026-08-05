const int Mod = 1e9 + 7 , Max = 1e7 + 5;
/*
Time  : O(N log log N)
Space : O(N)
Use   : Computes the Smallest Prime Factor (SPF) for every number from 1 to Max.
*/
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

const int Mod = 1e9 + 7 , Max = 1e7 + 5;
/*
Time  : O(N)
Space : O(N)
Use   : Computes the Smallest Prime Factor (SPF) for every number using the Linear Sieve algorithm.
*/
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

/*
Time  : O(log N)
Space : O(1)
Use   : Returns Euler's Totient Function φ(n), the count of integers in [1,n] that are coprime with n.
*/
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

/*
Time  : O(N)
Space : O(N)
Use   : Computes SPF, Euler's Totient (phi), and stores all prime numbers together using Linear Sieve.
*/
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
    // vector<int>().swap(spf); optimize for better memory ( free memory if SPF is no longer needed )
}

/*
Time  : O(log exponent)
Space : O(1)
Use   : Computes (base^exponent) % mod using Binary Exponentiation
*/
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

/*
Time  : O(log Mod)
Space : O(1)
Use   : Returns the Modular Multiplicative Inverse of a number (Mod must be prime).
*/
ll modinv(ll a) {
    return powmod(a, Mod - 2, Mod);
}

/*
Time  : O(sqrt(N))
Space : O(number of prime factors)
Use   : Returns the Prime Factorization of a number as (prime, exponent).
*/
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

/*
Time  : O(sqrt(N))
Space : O(number of divisors)
Use   : Returns all divisors of a number in arbitrary order.
*/
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

/*
Time  : O(sqrt(N))
Space : O(1)
Use   : Returns the Number of Divisors of a number.
*/
int number_of_divisors(ll n)
{
    int cnt = 0;
    for(ll i = 1; i * i <= n; i++)
        if(n % i == 0) cnt += (i * i == n) ? 1 : 2;
    return cnt;
}

/*
Time  : O(sqrt(N))
Space : O(1)
Use   : Returns the Sum of all Divisors of a number.
*/
ll sum_of_divisors(ll n)
{
    ll sum_divisors = 0;
    for(ll i = 1; i * i <= n; i++)
        if(n % i == 0)
        {
            sum_divisors += i;
            if(i * i != n) sum_divisors += n / i;
        }
    return sum_divisors;
}

/*
Time  : O(sqrt(N))
Space : O(1)
Use   : Returns the Sum of Divisors for every number in the range [1 ... N].
*/
 ll divisorSum(ll num){
    ll sum = 0;
    for (ll i = 1; i <= sqrt(num); i++) {
        ll t1 = i * (num / i - i + 1);
        ll t2 = (((num / i) * (num / i + 1)) / 2) - ((i * (i + 1)) / 2);
        sum += t1 + t2;
        }
        return sum;
}

/*
Time  : O(N log log N)
Space : O(N)
Use   : Computes all Prime Numbers up to Max using Sieve;
*/
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

/*
Time  : O(N)
Space : O(N)
Use   : Computes all Prime Numbers up to Max using the Linear Sieve.
*/
vector < bool > isPrime( Max ,1 );vector< int >primes;
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

const int Mod = 1e9 + 7
/*
Time  : O(1)
Space : O(1)
Use   : Returns (a + b) or ( a * b ) or ( a / b ) or ( a - b ) modulo Mod.
*/
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

/*
Time  : O(log(min(a,b)))
Space : O(log(min(a,b))) 
Use   : Solves ax + by = gcd(a,b) and returns valid x, y (Bezout's identity).
        Can be used to solve ax + by + c = 0:
        if a solution exists, k = (-c / gcd) ==> x*k , y*k is the answer.
        Also used to compute modular inverse when the mod is NOT prime.
*/
ll Extended_Euclidean(ll a, ll b, ll &x, ll &y)
{
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll g = Extended_Euclidean(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

/*
Time  : O(log Mod)
Space : O(1)
Use   : Returns Modular Inverse of a mod m, works even when m is NOT prime
        (requires gcd(a, m) == 1).
*/
ll modinv_ext(ll a, ll m)
{
    ll x, y;
    ll g = Extended_Euclidean(a, m, x, y);
    if(g != 1) return -1; // inverse doesn't exist
    return ((x % m) + m) % m;
}

/*
Time  : O(log N)
Space : O(1)
Use   : Computes (b * e) % mod safely, avoiding overflow when mod is close to
        the limits of ll (used inside Miller_Rabin / Pollard_Rho since normal
        multiplication a*b can overflow before taking % mod).
*/
ll BinMul(ll b, ll e, ll mod)
{
    ll res = 0;
    b %= mod;
    while(e > 0)
    {
        if(e & 1) res = (res + b) % mod;
        b = (b + b) % mod;
        e >>= 1;
    }
    return res;
}

/*
Time  : O(log e)
Space : O(1)
Use   : Computes (b ^ e) % mod using Binary Exponentiation, but multiplies
        using BinMul instead of normal (a*b)%mod, so it stays safe for large
        mod (up to ~1e18) without overflow.
        Use this instead of powmod() whenever mod can be large (like inside
        Miller_Rabin / Pollard_Rho). If mod is always small and fixed
        (like 1e9+7), powmod() is fine and faster.
*/
ll BinPow(ll b, ll e, ll mod)
{
    ll res = 1;
    b %= mod;
    while(e > 0)
    {
        if(e & 1) res = BinMul(res, b, mod);
        b = BinMul(b, b, mod);
        e >>= 1;
    }
    return res;
}

/*
Time  : O(log^3 N) per number, Rounds iterations (Rounds=20 is enough)
Space : O(1)
Use   : Probabilistic Primality Test, works correctly for N up to ~1e18
        (unlike sieve-based isPrime which is limited by array size Max ~1e7).
        Used to check if a large single number is prime, and as a base case
        inside Pollard's Rho factorization to stop splitting a factor once
        it becomes prime.
*/
bool Miller_Rabin(ll num, int Rounds = 20)
{
    if(num < 2) return false;
    if(num != 2 && num % 2 == 0) return false;

    ll d = num - 1;
    while(d % 2 == 0) d >>= 1;

    for(int loop = 1; loop <= Rounds; loop++)
    {
        ll a = rand() % (num - 1) + 1, temp = d;
        ll x = BinPow(a, temp, num);
        while(temp != num - 1 && x != 1 && x != num - 1)
        {
            x = BinMul(x, x, num);
            temp <<= 1;
        }
        if(x != num - 1 && temp % 2 == 0) return false;
    }
    // If we reach here, then the number is prime
    return true;
}
