#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define sp " "
#define nl "\n"
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define popcount  __builtin_popcountll

void fast() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

const int Max = 1e5 + 5 , LOG = 20;
vector < vector < int > > up;
vector < int > level;
vector < int > adj[Max];
int n;
void solve() {
    cin >> n;
    up.assign( n + 2 , vector < int > (LOG) );
    level.assign( n + 2 , 0 );
    // for(int i = 1; i <= n; i++) adj[i].clear();
    for(int i = 0; i < n-1; i++) 
    {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
   }
    function < void (int,int) > dfs = [&](int node , int par)
    {
        up[node][0] = par;
        for(int j = 1 ; j < LOG ; j++) up[node][j] = up[ up[node][j-1] ][j-1];
        for( auto &it : adj[node] )
        {
            if( it == par ) continue;
            level[it] = level[node] + 1;
            dfs( it , node );
        }
    };
    function < int (int,int) > LCA = [&](int u , int v) -> int
    {
        // let u bigger
        if( level[u] < level[v] ) swap( u , v );
        int k = level[u] - level[v];
        for(int j = LOG - 1 ; j >= 0 ; j--)
        {
            if( k >= (1 << j))
            {
                u = up[u][j];
                k -= ( 1 << j );
            }
        }
        if( u == v ) return u;
        for(int j = LOG - 1 ; j >= 0 ; j--)
        {
            if( up[u][j] != up[v][j] )
            {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];      
    };
    dfs(1,0);
} 

int main() {
    fast();
    int t = 1;
    // cin >> t;
    for(int i = 1 ; i <= t ; i++) {
        solve();
    }
    return 0;
}
