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
const int N = 100 + 5;
int dp[11][N][N][2];
int n , d;
string k;
const int Mod = 1e9 + 7;
int calc( int idx , int sum , int sum2 , int t )
{
    if( idx == n ) return (( sum % d == 0) and (sum2 % d == 0));
    int &ret = dp[idx][sum][sum2][t];
    if(ret != -1) return ret;
    ret = 0;
    int end = t ? k[idx] - '0' : 9 ;
    for(int i = 0 ; i <= end ; i++)
    {
        // ret = ( ret + calc( idx + 1 , ( ( ( sum * 10 ) + i ) % d ) , t and ( i == k[idx] - '0' ) ) ) % Mod;
        ret = ( ret + calc( idx + 1 , ( ( sum + i ) % d ), ( ( ( sum2 * 10 ) + i ) % d ) , t and ( i == k[idx] - '0' ) ) );
    }
    return ret;
}
void solve() {
    string a, b;
    d = 0;
    cin >> a >> b >> d;
    if( d >= 100 ) return void( cout << 0 << nl);
    memset( dp , -1 , sizeof dp );
    k = b;
    n = b.size();
    int ans = calc(0,0,0,1);
    int num = stoll(a);
    num--;
    a = to_string(num);
    n = a.size();
    k = a;
    memset( dp , -1 , sizeof dp );
    ans -= calc(0,0,0,1);
    cout << ans << nl;
}   

    
signed main()
{   
    fast();
    int tc = 1;
    cin >> tc;    
    for(int i = 1 ; i <= tc ; i++)
    {
        // cout << "Case " << i << ": ";
        solve();
        // if(tc) cout << nl;
    }
}
