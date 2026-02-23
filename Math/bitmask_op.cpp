bool knowbit(ll n,int i){ return (n>>i)&1LL; }
ll setbit(ll n,int i){ return n|(1LL<<i); } // make it 1
ll resetbit(ll n,int i){ return n&(~(1LL<<i)); } // make it zero
ll flip(ll n,int i){ return n^(1LL<<i); }
