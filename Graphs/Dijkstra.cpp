const int N = 1e6 + 5;
ll n , m ;
vector < pair < ll , ll > > adj[N];
vector < ll > ans(N) ;
bool vis[N];
vector < ll > par(N , -1) , path;
 
void dijkstra(ll start)
{
    priority_queue< pair< ll,ll >, vector < pair < ll,ll > >, greater< pair < ll,ll > > > pq;
    for(int i = 0; i <= n; i++) ans[i] = 1e15;
    ans[start] = 0;
    pq.push({0, start});

    while(!pq.empty())
    {
        auto [cost, node] = pq.top();
        pq.pop();

        if(cost > ans[node]) continue;

        for(auto &[c, to] : adj[node]) 
        {
            if(ans[to] > cost + c)
            {
                ans[to] = cost + c;
                pq.push({ans[to], to});
                par[to] = node;
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
