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
struct Trie
{
    struct Node
    {
        Node *ch[26];
        int prefix , end;
        Node()
        {
            memset( ch , 0 , sizeof ch );
            prefix = end = 0;
        }
    };
    Node *root = new Node();
    
    void insert( const string &s )
    {
        Node *cur = root;
        for( auto it : s )
        {
            int idx = it - 'a';
            if( cur->ch[idx] == 0 )
            {
                cur -> ch[idx] = new Node();
            }
            cur = cur -> ch[idx];
            cur -> prefix++;
        }
        cur -> end++;
    }

    // removes one occurrence of s
    bool del( const string &s )
    {
        if( count_string(s) == 0 ) return 0;
        Node *cur = root;
        for( auto it : s )
        {
            int idx = it - 'a';
            Node *nxt = cur -> ch[idx];
            nxt -> prefix--;
            if( nxt -> prefix == 0 ) cur -> ch[idx] = 0;
            cur = nxt;
        }
        cur ->end--;
        return 1;
    }

    int count_string( const string &s )
    {
        Node *cur = root;
        for( auto it : s )
        {
            int idx = it - 'a';
            if( cur->ch[idx] == 0 ) return 0;
            cur = cur -> ch[idx];
        }
        return cur -> end;
    }

    int count_prefix( const string &s )
    {
        Node *cur = root;
        for( auto it : s )
        {
            int idx = it - 'a';
            if( cur->ch[idx] == 0 ) return 0;
            cur = cur -> ch[idx];
        }
        return cur -> prefix;
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
