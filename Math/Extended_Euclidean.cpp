/*
it solves 
ax + by = gcd( a , b )
to get x , y valid
it can be used with Bézout's identity
to solve ax + by + c = 0 
if ans is found ( k = (-c / Gcd)) ==> x * k , y * k
*/ 
ll Extended_Euclidean( ll a , ll b , ll &x , ll &y )
{
    if( b == 0 )
    {
        x = 1;
        y = 0;
        return a;
    }
    ll go = Extended_Euclidean( b  , a % b , y , x);
    y -= ( a / b ) * x;
    return go;
}
