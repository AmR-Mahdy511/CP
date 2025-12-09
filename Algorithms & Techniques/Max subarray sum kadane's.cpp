ll kadane(ll n , vector < ll > &v)
{
     ll ans = INT_MIN , sum = 0;
    for(int i = 0 ; i < n ; i++){
        sum += v[i];
        ans = max(ans,sum);
        sum = max(sum , 0LL); // return neg values to zero to get max ans
    }
    return ans;   
}
