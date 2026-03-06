/*
the problem is 
How many numbers x are there in the range 0 to b, where the digit d occurs exactly k times in x
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define sp " "
#define nl "\n"
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define popcount  __builtin_popcount
 
void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
}
const int N = 1005;
void solve() {
    ll n,k,d; cin >> n >> k >> d;
    ll memo[20][20][2];
    string s;
    while (n)
    {
      s.push_back( (n % 10) + '0' );
      n /= 10;  
    }
    reverse(all(s));
    memset( memo , -1 , sizeof memo );
    function < ll (int,int,int) > dp = [&](int idx , int cnt , int t) -> ll
    {
        // base case
        if( idx > s.size() ) return 0;
        if(idx == s.size())
        {
            if( cnt == k ) return 1;
            else return 0;
        }

        ll &ret = memo[idx][cnt][t];
        if(ret != -1) return ret;
        ret = 0; // bc i count

        // i want this to generate numbers that is <= n so i need to know my ub of cur dig ( 0-->9 or 0 -->ub )

        /*
        t --> (tight) 
        if it is zero -> then number rw can be greater than n to avoid that we need to make ub equals cur dig
        if it is one -> we can make whatever we want from 0 - > 9 bc 100 % cur_number is less than n
        */
        int ub = (t) ? 9 : s[idx] - '0';
        
        for(int i = 0 ; i <= ub ; i++)
        {
            if( cnt + (i == d) <= k ) ret += dp( idx + 1 , cnt + (i == d) , t || (i < s[idx] - '0'));
        }
        return ret;
    };
    cout << dp(0,0,0);
}
 
int main() {
    fast();
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
