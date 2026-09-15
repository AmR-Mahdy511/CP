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
bool knowbit(ll n,int i){ return (n>>i)&1LL; }
ll setbit(ll n,int i){ return n|(1LL<<i); } // make it 1
ll resetbit(ll n,int i){ return n&(~(1LL<<i)); } // make it zero
ll flip(ll n,int i){ return n^(1LL<<i); }

struct Binary_Trie
{
    const int BIT = 30;
    struct Node
    {
        Node *ch[2];
        int frq[2];
        Node()
        {
            ch[0] = ch[1] = 0;
            frq[0] = frq[1] = 0;
        }
    };
    Binary_Trie(){};
    Node *root = new Node();
    
    void insert( int n )
    {
        Node *cur = root;
        for(int bit = BIT ; bit >= 0 ; bit--)
        {
            bool idx = knowbit( n , bit );
            if( cur->ch[idx] == 0 )
            {
                cur->ch[idx] = new Node();
            }
            cur -> frq[idx]++;
            cur = cur -> ch[idx] ;
        }
    }

    void del( int n , int i , Node *cur )
    {
        if( i == -1 ) return;
        bool idx = knowbit( n , i );
        del( n , i - 1 , cur -> ch[idx] );
        cur -> frq[idx]--;
        if( cur -> frq[idx] == 0 )
        {
            delete cur -> ch[idx];
            cur -> ch[idx] = 0;
        }
    }
    void del( int n ) { return del( n , 30 , root );}
    int Max_Xor( int n )
    {
        int ans = 0;
        Node *cur = root;
        for(int bit = BIT ; bit >= 0 ; bit--)
        {
            bool idx = knowbit( n , bit );
            bool target = idx ^ 1;
            if( cur->ch[target] == 0 ) cur = cur -> ch[idx];
            else cur = cur -> ch[target] , ans = setbit(ans , bit);
        }
        return ans;
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
