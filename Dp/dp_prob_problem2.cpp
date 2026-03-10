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
                        Dr Mostafa Saad video's problem
                        You are watching a soccer match. Each team can score at most one goal
                        per 5-minute interval. The game has 90 minutes, split into 18 intervals.

                        skillOfTeamA, skillOfTeamB: probability (0-100) that a team scores in a given interval.
                        Return probability that at least one team scores a prime number of goals.
*/  
void solve() {
    int a , b;
    cin >> a >> b;
    double memo[19][19][19];
    // memset( memo , -1 , sizeof memo ); // do not use memset when you use double memo
    for(int i = 0 ; i < 19 ; i++) for(int j = 0 ; j < 19 ; j++) for(int x = 0 ; x < 19 ; x++) memo[i][j][x] = -1.0;
    vector < bool > primes(19,0);
    primes[2] = 1; primes[3] = 1; primes[5] = 1; primes[7] = 1; primes[11] = 1; primes[13] = 1; primes[17] = 1;
    double a_prob = a / 100.0 , b_prob = b / 100.0;
    function < double (int,int,int) > prob = [&](int idx , int a_goals , int b_goals) -> double
    {
        if( idx > 18 ) return 0.0;
        if( idx == 18 ) return ( primes[a_goals] or primes [b_goals]) ? 1.0 : 0.0;

        double &ret = memo[idx][a_goals][b_goals];
        if(ret > -0.5) return ret;
        ret = 0.0;
        /*
        probabilities
        ( 0 , 0 ) prob(idx + 1 , a_goals , b_goals) * ( 1 - a_prob ) * ( 1 - b_prob )
        ( 1 , 0 ) prob(idx + 1 , a_goals + 1 , b_goals) * a_prob * ( 1 - b_prob )
        ( 0 , 1 ) prob(idx + 1 , a_goals , b_goals + 1) * ( 1 - a_prob ) * b_prob
        ( 1 , 1 ) prob(idx + 1 , a_goals + 1 , b_goals + 1) * a_prob * b_prob
        */
        ret += prob(idx + 1 , a_goals , b_goals) * ( 1 - a_prob ) * ( 1 - b_prob );
        ret += prob(idx + 1 , a_goals + 1 , b_goals) * a_prob * ( 1 - b_prob );
        ret += prob(idx + 1 , a_goals , b_goals + 1) * ( 1 - a_prob ) * b_prob;
        ret += prob(idx + 1 , a_goals + 1 , b_goals + 1) * a_prob * b_prob;

        return ret;
    };
    cout << fixed << setprecision(10) << prob(0,0,0) << nl;
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
