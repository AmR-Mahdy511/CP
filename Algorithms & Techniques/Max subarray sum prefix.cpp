ll max_sub_sum(ll n , vector < ll > &v)
{
    // make sure make ans as a min value that can not be reached
    ll ans = -1e16 , curr_sum = 0 , min_sum = 0;
    for(auto &a : v)
    {
        ans = max( ans , curr_sum + a - min_sum);
        curr_sum += a;
        min_sum = min(min_sum , curr_sum);
    }
    return ans;
}
