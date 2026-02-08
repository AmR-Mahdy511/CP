const int N = 1e6 + 5;
ll n , m ;
vector < pair < ll , ll > > adj[N];
vector < ll > ans(N) ;
bool vis[N];
vector < ll > par(N , -1) , path;
 
void dijkstra(ll start)
{
    priority_queue < pair < ll , ll > , vector < pair<ll,ll> >,greater< pair<ll,ll> > > pq;
    pq.push({0,start});
    for(int i = 1; i <= n; i++) ans[i] = 1e15;
    // vis[start] = 1;
    while(!pq.empty())
    {
        pair < ll , ll > p = pq.top();
        pq.pop();
        ll node = p.second , cost = p.first;
 
        if(cost > ans[node]) continue;
        if(vis[node]) continue;
 
        vis[node] = 1;
        ans[node] = cost;        
        for(auto &[a,b] : adj[node])
        {
            if(ans[a] > cost + b)
            {
                ans[a] = cost + b;
                pq.push({ans[a], a});
                par[a] = node;
            }
        }
    }
}
void get_path(ll st , ll e)
{
     if(ans[e] == 1e15) return;
    for(int i = e; i != -1; i = par[i]) path.push_back(i);
    // path.push_back(st);
    reverse(all(path));
}
