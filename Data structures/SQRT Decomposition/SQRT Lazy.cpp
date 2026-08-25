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
struct Sqrt_Lazy
{
    int n ;
    const int B = 400;
    vector < T > Block;
    vector < T > &v;
    vector < T > Lazy;

    // Build in o(n)
    Sqrt_Lazy( vector<T> &v ) : v(v)
    {
        n = v.size();
        int sz = ( n + B - 1 ) / B;
        Block.assign( sz , T(0));
        Lazy.assign( sz , T(0));
        for(int i = 0 ; i < n ; i++) Block[i/B] += v[i];
    }
    int Block_sz(int b)
    {
        return min( B , n - b*B );
    }
    // update in o(1)
    void update( int idx , T val )
    {
        if( idx < 0 or idx >= n ) return ;
        int cur_Block = idx / B;
        T old = v[idx] + Lazy[cur_Block];
        T dif = val - old;
        v[idx] += dif;
        Block[cur_Block] += dif;
    }
    void update( int l , int r , T val )
    {
        if( l > r ) swap(l,r);
        if( l < 0 or r < 0 or r >= n ) return ;
        int st = l / B , end = r / B;
        if( st == end )
        {
            // in the same block
            for(int i = l ; i <= r ; i++) v[i] += val , Block[st] += val;            
        }
        else
        {
            int Fi = (end * B) , Last = ( st + 1 ) * B;
            for(int i = l ; i < Last ; i++) v[i] += val , Block[st] += val;
            for(int i = st + 1 ; i < end ; i++ ) Lazy[i] += val;
            for(int i = Fi ; i <= r ; i++) v[i] += val , Block[end] += val;            
        }
    }
    // query in o(sqrt(n))
    T query(int idx)
    {
        if( idx < 0 or idx >= n ) return T(0);
        return v[idx] + Lazy[idx/B];
    }
    T query(int l , int r)
    {
        if( l > r ) swap(l,r);
        if( l < 0 or r < 0 or r >= n ) return T(0);
        T ans = T(0);
        int st = l / B , end = r / B;
        if( st == end )
        {
            // in the same block
            for(int i = l ; i <= r ; i++) ans += v[i] + Lazy[st];
        }
        else
        {
            int Fi = (end * B) , Last = ( st + 1 ) * B;
            for(int i = l ; i < Last ; i++) ans += v[i] + Lazy[st];
            for(int i = st + 1 ; i < end ; i++ ) ans += Block[i] + (Lazy[i] * Block_sz(i));
            for(int i = Fi ; i <= r ; i++) ans += v[i] + Lazy[end];
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