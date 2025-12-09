ll min_sub_sum(ll n , vector < ll > &v)
{
    // make sure make ans as a max value that can not be reached
    ll ans = 1e18 , curr_sum = 0 , min_sum = 0;
    for(auto &a : v)
    {
        ans = min( ans , curr_sum + a - min_sum);
        curr_sum += a;
        min_sum = max(min_sum , curr_sum);
    }
    return ans;
}
