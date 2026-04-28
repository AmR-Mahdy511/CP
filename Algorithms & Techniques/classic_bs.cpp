#include <bits/stdc++.h>
using namespace std;

vector<int> v; // array is in outer scope (must be sorted)

/*
Returns first index i such that v[i] >= x
(lower bound)
*/
function<int(int)> lower_bound_idx = [](int x) -> int {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
};

/*
Returns first index i such that v[i] > x
(upper bound)
*/
function<int(int)> upper_bound_idx =
[](int x) -> int {
    return upper_bound(v.begin(), v.end(), x) - v.begin();
};

/*
Returns last index i such that v[i] <= x
*/
function<int(int)> last_le =[](int x) -> int {
    int idx = lower_bound(v.begin(), v.end(), x) - v.begin();
    if (idx == 0) return -1;
    return idx - 1;
};

/*
Returns last index i such that v[i] < x
*/
function<int(int)> last_lt = [](int x) -> int {
    int idx = upper_bound(v.begin(), v.end(), x) - v.begin();
    if (idx == 0) return -1;
    return idx - 1;
};

/*
Count of elements < x
*/
function<int(int)> count_less =[](int x) -> int {
    return lower_bound(v.begin(), v.end(), x) - v.begin();
};

/*
Count of elements <= x
*/
function<int(int)> count_le =[](int x) -> int {
    return upper_bound(v.begin(), v.end(), x) - v.begin();
};

/*
Count of elements == x
*/
function<int(int)> count_eq =[](int x) -> int {
    return upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
};
/*
Count of elements >= x
*/
function<int(int)> count_ge = [](int x) -> int {
    return v.end() - lower_bound(v.begin(), v.end(), x);
};

/*
Count of elements > x
*/
function<int(int)> count_greater = [](int x) -> int {
    return v.end() - upper_bound(v.begin(), v.end(), x);
};
