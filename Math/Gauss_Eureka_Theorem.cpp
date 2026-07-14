    // check Check if Number is One Triangle Using BS in o ( log(n) )
    function < bool (ll) > isOneTriangle = [&](ll Num) -> bool
    {
        ll l = 0 , r = 1e7 , ans = 0;
        while( l <= r )
        {
            ll mid = l + (r - l) / 2;
            if(1ll * mid * (mid + 1) / 2 <= Num) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        return 1ll * ans * (ans + 1) / 2 == Num;
    };    

    // check Check if Number is One Triangle Using Formula in better time
    function < bool (ll) > isOneTriangle = [&](ll Num) -> bool
    {
        ll x = (-1 + sqrtl(1 + 8.0L * Num)) / 2;
    
        while(1LL * x * (x + 1) / 2 < Num) x++;
        while(1LL * x * (x + 1) / 2 > Num) x--;
    
        return 1LL * x * (x + 1) / 2 == Num;
    };

    // Check if Number is Sum of Two Triangle Numbers
    function < bool (ll) > isTwoTriangles = [&](ll Num) -> bool
    {
        set < ll > All;
    
        for(int i = 0 ; i < Num ; i++)
        {
            ll Val = 1LL * i * (i + 1) / 2;
    
            if(Val > Num) break;
    
            All.insert(Val);
        }
    
        for(auto &a : All)
        {
            if(Num - a > 0 && All.count(Num - a)) return 1;
        }
    
        return 0; // Note that : the smallest next valid ans will be always 3
    };

    // Minimum Number of Triangle Numbers will be always 1 or 2 or 3
    function < int (ll) > MinTriangleNumbers = [&](ll Num) -> int
    {
        if(isOneTriangle(Num))
            return 1;
    
        if(isTwoTriangles(Num))
            return 2;
    
        return 3;
    };
