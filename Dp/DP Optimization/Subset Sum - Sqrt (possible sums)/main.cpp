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

void solve() {
    int n ; cin >> n;
    vector < int > v(n);
    int Sum = 0;
    for(int i = 0 ; i < n ; i++) cin >> v[i] , Sum += v[i];
    bitset < 4000005 > bs;
    bs[0] = 1;
    for(int i = 0 ; i < n ; i++) bs |= ( bs << v[i] );
    vector < int > ans;
    for(int i = 1 ; i <= 4000004 ; i++)
    {
        if( bs[i] ) ans.push_back(i);
    }
    cout << ans.size() << nl;
    for( auto &a : ans ) cout << a << sp;
    // cout << nl; 
}   

    
signed main()
{   
    fast();
    int tc = 1;
    // cin >> tc;    
    while(tc--)
    {
        solve();
        // if(tc) cout << nl;
    }
}
