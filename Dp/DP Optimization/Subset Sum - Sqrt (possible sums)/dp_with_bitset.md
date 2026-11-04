# Bitset optimization for subset sum

## The trick

Instead of a `dp[sum]` boolean array, I use a `bitset` where bit `s` is `1` if the sum `s` can be made from some subset of the numbers.

For every number `x`, I update everything with one line:

```cpp
bs |= (bs << x);
```

`bs << x` shifts every reachable sum by `x` (this is "take `x`"), and `|=` keeps the old sums (this is "don't take `x`").

## Why it's faster

The normal dp does `O(n × S)` operations.
The bitset handles 64 bits in one operation, so it's `O(n × S / 64)`.

## Why `4000005`

In this problem `n × Max` was at most `4000000`, so the sum can never be bigger than that.
I added `5` just to be safe.

So the size of the bitset should be **up to the biggest possible sum**. Here that's `n × Max`, and in general it's whatever the max sum can be.
Bits shifted past the size are just dropped, so a size smaller than the max sum gives wrong answers.

## Code

```cpp
void solve() {
    int n ; cin >> n;
    vector < int > v(n);
    int Sum = 0;
    for(int i = 0 ; i < n ; i++) cin >> v[i] , Sum += v[i];
    bitset < 4000005 > bs;
    bs[0] = 1;
    for(int i = 0 ; i < n ; i++) bs |= ( bs << v[i] );
    vector < int > ans;
    for(int i = 1 ; i <= 4000004 ; i++)
    {
        if( bs[i] ) ans.push_back(i);
    }
    cout << ans.size() << nl;
    for( auto &a : ans ) cout << a << sp;
}
```

This prints how many different sums (> 0) can be made, then the sums themselves.

## How to use it in any code

1. Replace the boolean dp `dp[s]` with `bitset<MAXS> bs`, and set `bs[0] = 1`.
2. For each number `x`: `bs |= (bs << x)`.
3. Check `bs[s]` to know if sum `s` is possible.
4. Set `MAXS` to the max possible sum (`n × Max`) + a few extra.
5. Declare it as a global or call `bs.reset()` per test, because it's not cleared between test cases.

## Notes

- It only answers "possible or not". If I need counts or the minimum number of items, I still need the normal dp.
- The final loop can go up to `Sum` instead of `4000004` to save time.
