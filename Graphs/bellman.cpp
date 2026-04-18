const int N = 5005;
struct edge{
int a,b;
ll cost;
};
vector < edge > edges(N) , edges2(N);
vector < ll > dis(N , 1e18);
ll n,m;
bool ok = 1;
bool vis1[N] , vis2[N];

ll bellman(int st)
{
    for(int i = 1 ; i <= n ; i++) dis[i] = 1e18;

    dis[st] = 0;

    for(int i = 1 ; i < n ; i++)
    {
        for(auto &e : edges)
        {
            if(dis[e.a] != 1e18 && dis[e.a] + e.cost < dis[e.b])
            {
                dis[e.b] = dis[e.a] + e.cost;
            }
        }
    }
}
// ===================================================================
const int N = 5005;
vector < Edge > edges;
vector < ll > dis( N , 1e18 );
vector < bool > cycled( n + 2 , 0 );
// do not forget edges.clear(); 
        function < void(int) > bellman = [&](int st) -> void
        {
            for(int i = 0 ; i <= n ; i++) dis[i] = 1e18 , cycled[i] = 0;
            dis[st] = 0;
            for(int step = 1 ; step < n  ; step++)
            {
                for( auto &[u,v,cost] : edges )
                {
                    if( dis[u] + cost < dis[v] and dis[u] != 1e18 ) dis[v] = dis[u] + cost ;
                }
            }
            for(int step = 1 ; step < n ; step++)
            {
                for( auto &[u,v,cost] : edges )
                {
                    if( dis[u] + cost < dis[v] and dis[u] != 1e18 ) cycled[v] = 1;
                }
            }          
            for(int step = 1 ; step < n ; step++)
            {
                for( auto &[u,v,cost] : edges )
                {
                    if( cycled[u] ) cycled[v] = 1;
                }
            }                 
        };
