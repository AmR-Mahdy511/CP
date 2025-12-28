/*
    Sqrt Decomposition
    -------------------
    Time Complexity:
    - Build: O(n)
    - Update: O(1)
    - Query: O(3√n)
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SqrtDecomposition {
private:
    ll n;                        // size of array
    ll BS;                       // size of each block
    vector< ll > arr;            // the given array
    vector< ll > block_sum;      // sum of each block

public:
    // just constructor (not necessary)
    SqrtDecomposition(int n) {
        this->n = n;
        BS = sqrtl(n) + 1; 
        arr.assign(n, 0);
        block_sum.assign(1005, 0); // take care of block size √1e6 = 1000
    }

    // Build decomposition
    void build(const vector< ll > &input)
    {
        for (int i = 0; i < n; i++) {
            arr[i] = input[i];
            block_sum[i / BS] += arr[i];
        }
    }

    // Point Update: arr[index] = value
    void update(int index, ll value) {
        int block = index / BS;
        block_sum[block] -= arr[index];
        arr[index] = value;
        block_sum[block] += arr[index];
    }

    // Range Sum Query [l, r]
    ll query(int l, int r) 
    {
        ll sum = 0;

        ll start = l / BS;
        ll end   = r / BS;

        if (start == end) 
        {
            // in the same block
            for (int i = l; i <= r; i++)
                sum += arr[i];
        }
         else
          {
            // o( 3√n )
            // iterate first block
            int endFirst = (start + 1) * BS - 1;
            for (int i = l; i <= endFirst; i++)
                sum += arr[i];

            // calc other blocks
            for (int b = start + 1; b <= end - 1; b++)
                sum += block_sum[b];

            // iterate last block
            int startLast = end * BS;
            for (int i = startLast; i <= r; i++)
                sum += arr[i];
        }

        return sum;
    }
};
