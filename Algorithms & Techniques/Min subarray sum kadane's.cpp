ll kadane_min(ll n, vector<ll> &v) {
    // make sure that ans is a max value that can not be reached
    ll ans = LLONG_MAX, sum = 0;
    for(int i = 0; i < n; i++) {
        sum += v[i];
        ans = min(ans, sum); // just min ans
        sum = min(sum, 0LL); // min curr sum
    }
    return ans;
}
