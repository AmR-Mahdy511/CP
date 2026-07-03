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
        int cur = pi[n - 1];
        while(cur)
        {
            vis[cur] = 1;
            cur = pi[cur - 1];
        }
        return vis;
    }
    // Get the smallest period of the string, smallest p such that s[i] == s[i % p] for all i
    int smallest_period( const vector<int> &pi )
    {
        int k = n - pi[n - 1];
        return (n % k == 0 ? k : n);
    }  
    // Check if string is made of repetitions of its smallest period
    bool is_periodic( const vector<int> &pi )
    {
        return smallest_period(pi) != n;
    }
    // take care it's n ^ 2
    ll cnt_dist_substrings( const string &s )
    {
        ll All = 0;
        string cur;
        for(int i = 0 ; i < n ; i++)
        {
            cur += s[i];
            string rev = cur;
            reverse( all(rev) );
            vector < int > pi;
            KMP(rev, pi);
            int Max = 0;
            for(int x : pi) Max = max( Max , x );
            All += cur.size() - Max;
        }
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
    void KMP_automaton( const string &s , vector < vector < int > > &aut  , vector < int > &pi )
    {
        string temp = s + "#";
        int n = temp.size();
        aut.assign( n + 1 , vector < int > (26) );
        for(int i = 0 ; i < n ; i++)
        {
            for(int ch = 0 ; ch < 26 ; ch++)
            {
                if( i and ( temp[i] - 'a' != ch ) )
                {
                    aut[i][ch] = aut[pi[i-1]][ch];
                }
                else aut[i][ch] = i + ( temp[i] - 'a' == ch ) ;
            }
        }
    }
};
