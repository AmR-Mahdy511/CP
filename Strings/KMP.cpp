struct KMP
{
    int n ;
    KMP( const string &s , vector < int > &pi )
    {
        n = s.size();
        pi.assign( n , 0 );
        for(int i = 1 , j = 0 ; i < n ; i++)
        {
            while( j and s[i] != s[j] ) j = pi[j-1];
            if( s[i] == s[j] ) j++;
            pi[i] = j;
        }
    } 
    // marks all lengths that are both prefix and suffix
    vector < bool > prefix_equal_suffix( const vector < int > &pi )
    {
        vector < bool > vis( n + 2 , 0 );
        int cur = n - 1 ;
        while( pi[cur] )
        {
            vis[pi[cur]] = 1;
            cur = pi[cur-1];
        }
        return vis;
    }
    // Get the smallest period of the string, smallest p such that s[i] == s[i % p] for all i
    int smallest_period( const vector< int > &pi )
    {
        return n - pi[n - 1];
    }    
    // Check if string is made of repetitions of its smallest period
    bool is_periodic( const vector< int > &pi )
    {
        return n % smallest_period(pi) == 0;
    }    
    ll cnt_dist_substrings( const vector < int > &pi )
    {
        ll All = 0;
        for(int i = 0 ; i < n ; i++) All += i - pi[i];
        return All;
    }
    vector < ll > cnt_prefix_freq( const vector < int > &pi )
    {
        vector < ll > freq( n + 2 , 0 );
        for(int i = 0 ; i < n ; i++) freq[pi[i]]++;
        for(int i = n - 1 ; i > 0 ; i--) freq[pi[i-1]] += freq[i];
        for(int i = 1 ; i <= n ; i++) freq[i]++;
        return freq;
    }
};
