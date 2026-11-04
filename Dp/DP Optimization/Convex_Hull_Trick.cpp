// ==========================================================
// Dynamic Convex Hull Trick for DP Optimization
//
// Solves DP problems like:
//
//      dp[i] = max(dp[j] + m[j] * x[i])
//      dp[i] = min(dp[j] + m[j] * x[i])
//
// Every previous DP state is represented as a line:
//      y = kx + m
//
// add(k, m)  -> insert a new line.
// query(x)   -> get the maximum value at x.
//
// Complexity:
//      add()   : O(log N)
//      query() : O(log N)
//
// For minimum queries:
//      hull.add(-k, -m);
//      answer = -hull.query(x);
// ==========================================================

// Dynamic Convex Hull Trick for DP optimization

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Line {
    mutable int k, m, p;
    bool operator<(const Line& o) const { return k < o.k; } // sort by slope
    bool operator<(int x) const { return p < x; } // used for binary search while querying
};

struct DynamicLineContainer : multiset<Line, less<>> {

    // Infinity value for the last line
    static const int inf = INT64_MAX;

    // Floor division (handles negative numbers correctly)
    int div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    // Compute the intersection between two lines
    // Also updates the last x where line x is better than line y
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }

    // Insert a new line: y = kx + m
    // Removes all useless lines automatically
    void add(int k, int m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    // Query the maximum value at x
    int query(int x) {
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

// to use:
//
// DynamicLineContainer hull;
//
// hull.add(slope, intercept);
//
// hull.query(x);
//
// to convert min queries to max queries:
//
// hull.add(-slope, -intercept);
//
// -hull.query(x);


// Example: https://codebreaker.xyz/problem/cht
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    int a[n], b[n];

    DynamicLineContainer hull;

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int dp[n];
    dp[0] = 0;

    // First DP state becomes the first line
    hull.add(a[0], 0);

    for (int i = 1; i < n; i++) {

        // Get the best previous line at x = b[i]
        dp[i] = hull.query(b[i]);

        // Current DP state becomes a new line
        hull.add(a[i], dp[i]);
    }

    cout << dp[n - 1] << '\n';
}
