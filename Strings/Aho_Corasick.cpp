#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define all(x) x.begin(), x.end()
 
void fast()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);  
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}
vector < string > pats;
struct AC {
    int N, P;
    const int A = 26;
    vector <vector <int>> next;
    vector <int> link, out_link;
    vector <vector <int>> out;
    AC(): N(0), P(0) {node();}
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get (char c) {
        return c - 'a';
        // return (unsigned char)c;
    }
    void add_pattern (const string T, int idx) {
        int u = 0;
        for (auto c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(idx);
    }
    void compute() {
        queue <int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front(); q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance (int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
    string smallest(int L){ 
        string res;
        int u = 0;
        for (int i = 0;i < L;i++){
            for (int c = 0;c < 26;c++){
                int v = next[u][c]; 
                if (out[v].empty() and !out_link[v]){
                    res.push_back(char('a' + c));
                    u = v;
                    break;
                }
            }
        }
        return res;
    }
 
    bool contains(const string &s) {
        int u = 0;
        for (char c : s) {
            u = advance(u, c);
            if (!out[u].empty() || out_link[u]) return true;
        }
        return false;
    }
    vector < int >  first_idx(const string &s , int n ) {
        int u = 0 ;
        vector < int > frq(N , -1);
        vector < int > res(n , -1);
        for (int i = 0 ; i < s.size() ; i++) {
            u = advance(u, s[i]);
            for (int v = out[u].empty() ? out_link[u] : u; v; v = out_link[v])
            {          
                if( frq[v] != -1 ) break;
                frq[v] = i;
            }
        }
        for(int i = 0 ; i < n ; i++)
        {
            int u = 0 ;
            for(auto &c : pats[i] )
            {
                u = advance( u , c );
            }
            if (frq[u] != -1) res[i] = frq[u] - (int)pats[i].size() + 1;
        }
        return res;
    }
    vector < vector < int > >  all_idx(const string &s , int n ) {
        int u = 0 ;
        vector < vector < int > > frq(N);
        vector < vector < int > > res(n);
        for (int i = 0 ; i < s.size() ; i++) {
            u = advance(u, s[i]);
            for (int v = out[u].empty() ? out_link[u] : u; v; v = out_link[v])
            {          
                // if( frq[v] != -1 ) break;
                frq[v].push_back(i);
            }
        }
        for(int i = 0 ; i < n ; i++)
        {
            int u = 0 ;
            for(auto &c : pats[i] )
            {
                u = advance( u , c );
            }
        //    res[i].push_back(frq[u] - pats[i].size() + 1);
        for (auto &e : frq[u]) res[i].push_back(e - (int)pats[i].size() + 1);
        }
        return res;
    }
    vector < int > match(const string &s, int k) {
        vector < int > res( k , 0 );
        int u = 0;
        for (char c : s) {
            u = advance(u, c);
            for (int v = out[u].empty() ? out_link[u] : u; v; v = out_link[v])
            {
                for (int id : out[v]) res[id]++;  
            }
        }
        return res;
    }

};

void solve() {

}

signed main()
{   
    fast();
    int tc = 1;
    // cin >> tc;    
    while(tc--) 
    {
        solve();
        // if(tc) cout << nl;
    }
}   
