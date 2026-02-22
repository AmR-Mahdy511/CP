bool knowbit(ll n,int i){ return (n>>i)&1; }
ll setbit(ll n,int i){ return n|(1<<i); }
ll resetbit(ll n,int i){ return n&(~(1<<i)); }
ll flip(ll n,int i){ return n^(1<<i); }
