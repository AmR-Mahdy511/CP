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

int cur;
struct Query
{
    int l , r , id;
};
const int Max = 1e6 + 5;
int frq[Max];
vector < int > v;
void add(int val)
{
    frq[val]++;
    if( frq[val] == 1 ) cur++;
}
void del(int val)
{
    frq[val]--;
    if( frq[val] == 0 ) cur--;
}
vector < int > MO(vector < Query > &Q)
{
    int n = v.size();
    const int B = sqrt(n) + 1;
    vector < int > ans(Q.size());
    sort(all(Q) , [&](const Query x , const Query y ) -> bool
    { return make_pair( x.l / B , x.r) < make_pair( y.l / B , y.r) ;} );
    int l = Q[0].l , r = Q[0].l;
    add(v[l]);
    for( auto &[lq , rq , id] : Q )
    {
        // r -> ,  l -> , l <- , r <-
        while( r < rq ) add(v[++r]);
        while( l < lq ) del(v[l++]);
        while( l > lq ) add(v[--l]);
        while( r > rq ) del(v[r--]);
        ans[id] = cur;
    }
    return ans;
}
void solve() {
  
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
