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
int rand( int l , int r )
{
    return uniform_int_distribution<int>( l , r )( rng );
}

// don't forget this
const int Mod1 = 1e9 + 7;
const int Mod2 = 1e9 + 9;

const int Base1 = rand(31 , 1e9);
const int Base2 = rand(31 , 1e9);

template < typename T >
struct Hashed_Deque
{
private:
    deque < T > dq;
    pair < ll , ll > Hash = {0 , 0};
    vector < ll > pw1{1} , invpw1{1};
    vector < ll > pw2{1} , invpw2{1};
    ll invBase1 = -1 , invBase2 = -1; 
    int n = 0;
    ll PowMod(ll b,ll e,ll mod)
    {
        ll res = 1;
        while(e)
        {
            if(e & 1) res = res * b % mod;
            b = b * b % mod;
            e >>= 1;
        }
        return res;
    }

    void precalc(int sz)
    {
        if((int)pw1.size() > sz) return; 

        if(invBase1 == -1)
        {
            invBase1 = PowMod(Base1 , Mod1 - 2 , Mod1);
            invBase2 = PowMod(Base2 , Mod2 - 2 , Mod2);
        }

        while((int)pw1.size() <= sz)
        {
            pw1.push_back(pw1.back() * Base1 % Mod1);
            invpw1.push_back(invpw1.back() * invBase1 % Mod1);

            pw2.push_back(pw2.back() * Base2 % Mod2);
            invpw2.push_back(invpw2.back() * invBase2 % Mod2);
        }
    }

public:

    Hashed_Deque(){}
    Hashed_Deque(int mxSize)
    {
        precalc(mxSize);
    }
    
    int size()
    {
        return n;
    }

    bool empty()
    {
        return n == 0;
    }

    void clear()
    {
        dq.clear();
        n = 0;
        Hash = {0 , 0};
    }

    pair < ll , ll > get()
    {
        return Hash;
    }

    void push_back(T x)
    {
        precalc(n + 1);
        Hash.first = ( Hash.first * Base1 + x ) % Mod1;
        Hash.second = ( Hash.second * Base2 + x ) % Mod2;
        dq.push_back(x);
        n++;
    }

    void push_front(T x)
    {
        precalc(n + 1);
        Hash.first = ( x * pw1[n] + Hash.first ) % Mod1;
        Hash.second = ( x * pw2[n] + Hash.second ) % Mod2;
        dq.push_front(x);
        n++;
    }
    void pop_back()
    {
        if(n == 0) return;
        Hash.first =( (Hash.first - dq.back() + Mod1) % Mod1 ) * invpw1[1] % Mod1;
        Hash.second = ( (Hash.second - dq.back() + Mod2) % Mod2 ) * invpw2[1] % Mod2;
        dq.pop_back();
        n--;
    }

    void pop_front()
    {
        if(n == 0) return;
        n--;
        Hash.first = ( Hash.first - dq.front() * pw1[n] % Mod1 + Mod1 ) % Mod1;
        Hash.second = ( Hash.second - dq.front() * pw2[n] % Mod2 + Mod2 ) % Mod2;
        dq.pop_front();
    }

    T front()
    {
        return dq.front();
    }

    T back()
    {
        return dq.back();
    }

    bool operator == (const Hashed_Deque < T > &rhs) const
    {
        return n == rhs.n && Hash == rhs.Hash;
    }

    bool operator != (const Hashed_Deque < T > &rhs) const
    {
        return !((*this) == rhs);
    }
};   

void solve() {
    string s = "abccba"; 

    Hashed_Deque<int> forward, backward;

    for(auto c : s) forward.push_back(c);
    for(int i = (int)s.size() - 1; i >= 0; i--) backward.push_back(s[i]);

    if(forward == backward)
        cout << "Palindrome" << nl;
    else
        cout << "Not Palindrome" << nl;

    Hashed_Deque<int> dq;
    for(auto c : s) dq.push_back(c);

    while(dq.size() > (int)s.size() / 2 + 1)
    {
        dq.pop_back();
        dq.pop_front();
    }

    cout << "remaining size = " << dq.size() << nl;
    cout << "middle part hash = " << dq.get().first << sp << dq.get().second << nl;
}

signed main() {
    fast();
    int t = 1;
    // cin >> t;
    for(int i = 1 ; i <= t ; i++) {
        solve();
        if( i != t ) cout << nl;
    }
    return 0;
}
