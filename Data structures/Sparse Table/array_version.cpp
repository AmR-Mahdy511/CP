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

const int MAXN = 200005;
const int MAXLOG = 18;

template<class T>
struct SparseTable {
    int n , LOG;
    T table[MAXN][MAXLOG];
    int Log[MAXN + 1];

    // operation (change it if needed)
    T merge(T a , T b) {
        return max(a , b); // change to min / gcd / etc
    }

    // initialize sizes + log table
    void init() {
        LOG = (n == 0) ? 1 : 32 - __builtin_clz(n);
        Log[0] = Log[1] = 0;

        for(int i = 2 ; i <= n ; i++)
            Log[i] = Log[i / 2] + 1;
    }

    // build sparse table O(n log n)
    void build(T v[]) {
        for(int i = 0 ; i < n ; i++)
            table[i][0] = v[i];

        for(int j = 1 ; j < LOG ; j++) {
            for(int i = 0 ; i + (1 << j) <= n ; i++) {
                table[i][j] = merge(  table[i][j - 1], table[i + (1 << (j - 1))][j - 1] );
            }
        }
    }

    // init + build from array
    void assign(int _n , T v[]) {
        n = _n;
        init();
        build(v);
    }

    // query range [L, R] in O(1) ( zero based )
    T query(int L , int R) {
        int j = Log[R - L + 1];
        return merge( table[L][j], table[R - (1 << j) + 1][j]  );
    }
};

int arr[MAXN];
SparseTable<int> st;

void solve()
{
    int n ; cin >> n;
    for(int i = 0 ; i < n ; i++) cin >> arr[i];
    st.assign( n , arr );
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
