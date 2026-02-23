bool knowbit(ll n,int i){ return (n>>i)&1LL; }
ll setbit(ll n,int i){ return n|(1LL<<i); }
ll resetbit(ll n,int i){ return n&(~(1LL<<i)); }
ll flip(ll n,int i){ return n^(1LL<<i); }
