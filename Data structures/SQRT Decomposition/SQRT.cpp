#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define all(x) x.begin(), x.end()
 
void fast()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

template< typename T >
struct SQRT
{
    int n ;
    const int B = 400;
    vector < T > Block;
    vector < T > &v;

    // Build in o(n)
    SQRT( vector<T> &v ) : v(v)
    {
        n = v.size();
        int sz = ( n + B - 1 ) / B;
        Block.assign( sz , T(0));
        for(int i = 0 ; i < n ; i++) Block[i/B] += v[i];
    }

    // update in o(1)
    void update( int idx , T val )
    {
        Block[idx/B] -= v[idx];
        v[idx] = val;
        Block[idx/B] += val;
    }

    // query in o(sqrt(n))
    T query(int l , int r)
    {
        if( l > r ) swap(l,r);
        if( l < 0 or r < 0 or r >= n ) return T(0);
        T ans = T(0);
        int st = l / B , end = r / B;
        if( st == end )
        {
            // in the same block
            for(int i = l ; i <= r ; i++) ans += v[i];
        }
        else
        {
            int Fi = (end * B) , Last = ( st + 1 ) * B;
            for(int i = l ; i < Last ; i++) ans += v[i];
            for(int i = st + 1 ; i < end ; i++ ) ans += Block[i];
            for(int i = Fi ; i <= r ; i++) ans += v[i];
        }
        return ans;
    }
};

void solve() {

}
 
signed main()
{
    fast();
    int tc = 1;
    cin >> tc;    
    while(tc--)
    {
        solve();
        // if(tc) cout << nl;
    }
}