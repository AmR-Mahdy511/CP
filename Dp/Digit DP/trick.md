# Digit DP trick: `memset` once and reuse the dp across all test cases

## The trick

When a digit DP problem has many test cases, I don't reset the dp for every test.
I call `memset(dp, -1, sizeof dp)` **once, outside the `while(tc--)` loop**, and I keep running `calc` on every test.
All the states computed in previous tests are already in the dp, so I never compute them again.

> Fe kol test ba3mel run lel `calc` 3ady, w el states elly etehsebet fel tests elly fatet bt-kon gahza.

## Why it works

A state with `t = 0` (not tight) means the remaining digits are free (`0..9`), so its answer does **not** depend on `N`.
It is the same in every test.
Only the tight states (`t = 1`) depend on `N`, and there is one tight path per test.

So I need two things:

1. **Pad `N` with leading zeros to a fixed length**, so `idx` means the same thing in every test:
   ```cpp
   s = string(19 - s.size(), '0') + s;
   n = 19;
   ```
2. **Read from and write to the dp only when `t == 0`.**

## Code

```cpp
int dp[19][1 << 10][2][10][2];
string s;
int n;

int calc(int idx, int mask, int t, int Max, int st)
{
    if (idx == n)
        return __builtin_popcount(mask) == Max and st;

    int &memo = dp[idx][mask][t][Max][st];
    if (!t and ~memo)
        return memo;

    int ret = 0;
    int end = t ? s[idx] - '0' : 9;
    for (int i = 0; i <= end; i++)
    {
        int nt = t and (i == s[idx] - '0');
        if (i == 0 and st == 0) ret += calc(idx + 1, mask, nt, Max, 0);
        else ret += calc(idx + 1, setbit(mask, i), nt, max(Max, i), 1);
    }
    if (!t) memo = ret;
    return ret;
}

void solve()
{
    cin >> s;
    s = string(19 - s.size(), '0') + s;
    n = 19;
    cout << calc(0, 0, 1, 0, 0) << nl;
}

signed main()
{
    fast();
    int tc = 1;
    cin >> tc;
    memset(dp, -1, sizeof dp);   // once only
    while (tc--) solve();
}
```

The problem here: count the numbers in `[0, N]` where the number of distinct digits equals the max digit.
`t` = tight, `st` = started (so leading zeros don't count), `mask` = digits used, `Max` = max digit.

## How to use it in any code

1. Write `calc(idx, ...state..., t, st)` the normal way.
2. Pad `N` to a fixed length.
3. Read and write the dp only when `t == 0`.
4. Make sure the state has nothing specific to one test (like `K` if it changes per test).
   If it does, add it to the dp dimensions or `memset` per test.
5. `memset` once before the `while(tc--)` loop.

## Careful

Don't write `int &ret = dp[...]` and then modify `ret`. That also writes the tight states into the dp,
and they stay stale for the next test. Use a local `ret` and store into the dp only when `!t`.
