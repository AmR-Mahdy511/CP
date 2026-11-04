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
bool knowbit(ll n,int i){ return (n>>i)&1LL; }
ll setbit(ll n,int i){ return n|(1LL<<i); } // make it 1
ll resetbit(ll n,int i){ return n&(~(1LL<<i)); } // make it zero
ll flip(ll n,int i){ return n^(1LL<<i); }


int dp[19][1 << 10][2][10][2];
string s;
int n ;
int calc( int idx , int mask , int t , int Max , int st )
{
    if( idx == n ) 
        return __builtin_popcount(mask) == Max and st ;
    if( Max > 9 ) 
        return 0;
    int &ret = dp[idx][mask][t][Max][st];
    if(~ret)
        return ret;
    ret = 0;
    int end = t ? s[idx] - '0' : 9;
    for(int i = 0 ; i <= end ; i++)
    {
        int cur_Max = max( Max , i );
        if( i == 0 and st == 0 ) ret += calc( idx + 1 , mask , t and ( i == s[idx] - '0') , Max, 0 );
        else ret += calc( idx + 1 , setbit(mask,i) , t and ( i == s[idx] - '0') , cur_Max , 1 );
    }
    if(!t)
        dp[idx][mask][t][Max][st] = ret;
    return ret;
}
void solve() {
    cin >> s;
    s = string(19 - s.size(), '0') + s;
    n = 19;
    cout << calc( 0 , 0 , 1 , 0 , 0 ) << nl;
}   


signed main()
{   
    fast();
    int tc = 1;
    cin >> tc;    
    memset( dp , -1 ,sizeof dp);
    while(tc--)
    {
        solve();
        // if(tc) cout << nl;
    }
}
