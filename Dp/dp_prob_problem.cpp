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
/*
                            You have a fair six-sided die. You roll it N times.
                            What is the probability that the sum of the rolls equals S?
                            (1 ≤ N ≤ 50)                         (1 ≤ S ≤ 6*N)
*/  
void solve() {
    int n , s;
    cin >> n >> s;
    vector < vector < double > > memo ( 55 , vector < double > (305 , -1));    
    function < double ( int , int ) > prob = [&]( int idx , int sum ) -> double
    {
        if( idx > n ) return 0.0; 
        if( idx == n ) return (sum == s) ? 1.0 : 0;

        double &ret = memo[idx][sum];
        if( ret != ret ) return ret; // like ret != -1 but bc we operate with doubles so that's works instead
        
        ret = 0.0;
        for(int cur_face = 1 ; cur_face <= 6 ; cur_face++)
        {
            ret += prob( idx + 1 , sum + cur_face ) / 6.0;
        }
        return ret;
    };
    cout << fixed << setprecision(10) << prob(0,0) << nl;
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
