#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long 
#define ull unsigned long long
#define ld long double
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
template<class T>
struct SparseTable {
    int n , LOG;
    vector<vector<T>> table;
    vector<int> Log;

    // operation (change it if needed)
    T merge(T a , T b) {
        return max(a , b); // change to min / gcd / etc
    }

    // initialize sizes + log table
    void init() {
        LOG = 32 - __builtin_clz(n);
        table.assign(n , vector<T>(LOG));
        Log.assign(n + 1 , 0);

        for(int i = 2 ; i <= n ; i++)
            Log[i] = Log[i / 2] + 1;
    }

    SparseTable() {}

    // init only with size
    SparseTable(int _n) {
        n = _n;
        init();
    }

    // init + build from array
    SparseTable(int _n , vector<T>& v) {
        n = _n;
        init();
        build(v);
    }

    // build sparse table O(n log n)
    void build(vector<T>& v) {
        for(int i = 0 ; i < n ; i++)
            table[i][0] = v[i];

        for(int j = 1 ; j < LOG ; j++) {
            for(int i = 0 ; i + (1 << j) <= n ; i++) {
                table[i][j] = merge(
                    table[i][j - 1],
                    table[i + (1 << (j - 1))][j - 1]
                );
            }
        }
    }

    // query range [L, R] in O(1) ( zero based )
    T query(int L , int R) {
        int j = Log[R - L + 1];
        return merge(
            table[L][j],
            table[R - (1 << j) + 1][j]
        );
    }
};

void solve()
{
    int n ; cin >> n;
    vector < int > v(n);
    for(int i = 0 ; i < n ; i++) cin >> v[i];
    SparseTable < int > st( n , v );
    cout << st.query( 0 , 4 ) << nl;
    cout << st.query( 0 , 2 ) << nl;
    cout << st.query( 2 , 3 ) << nl;
}

signed main() {
    fast();
    int t = 1;
    // cin >> t;
    for(int i = 1 ; i <= t ; i++) {
        solve();
    }
    return 0;
}
