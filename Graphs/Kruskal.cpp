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
struct Edge
{
    int u , v , cost;
    Edge(int u , int v , int cost) : u(u), v(v), cost(cost) {}
    bool operator < ( const Edge&b ) const{ return cost < b.cost; }
};
struct dsu{
    vector < int > parent;
    dsu(int n) { parent.assign( n + 1 , - 1); }

    int find( int u )
    {
        if( parent[u] < 0 ) return u;
        return parent[u] = find(parent[u]);
    }
    int same_group( int u , int v ) { return find(u) == find(v); }
    int get_size( int u ){ return -parent[find(u)]; }
    bool merge( int u , int v )
    {
        int fi_leader = find(u) , sec_leader = find(v);
        if( fi_leader == sec_leader ) return 0;
        
        // fi leader is bigger than sec
        if( -parent[fi_leader] < -parent[sec_leader] ) swap( fi_leader , sec_leader );
        parent[fi_leader] += parent[sec_leader];
        parent[sec_leader] = fi_leader;
        return 1; 
    }
};

void solve() {
    int n , m;
    cin >> n >> m;
    vector < Edge > edges;
    for(int i = 0 ; i < m ; i++)
    {
        int u , v , cost;
        cin >> u >> v >> cost;
        edges.push_back( Edge(u,v,cost) );
    }
    sort(all(edges));
    dsu d( n + 1 );
    ll ans = 0;
    for( auto &[u,v,cost] : edges )
    {
        if( d.same_group(u,v) ) continue;
        d.merge(u,v);
        ans += cost;
    }
    cout << ans << nl;
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
