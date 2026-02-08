const int N = 5005;
struct edge{
int a,b;
ll cost;
};
vector < edge > edges(N) , edges2(N);
vector < ll > dis(N , -1e17);
ll n,m;
bool ok = 1;
bool vis1[N] , vis2[N];

ll bellman(ll st)
{
    dis[st] = 0;
    for(int i = 1 ; i < n ; i++)
    {
        for(auto &e : edges)
        {
            if(dis[e.a] > -1e17 &&  dis[e.b] < dis[e.a] + e.cost)
            {
                dis[e.b] = dis[e.a] + e.cost;
            }
        }
    }

    for(int i = 1 ; i <= n ; i++)
    {
        for(auto &e : edges)
        {
            if(dis[e.a] > -1e17 &&  dis[e.b] < dis[e.a] + e.cost)
            {
                if(vis1[e.a] && vis2[e.b])
                {
                    return -1;
                }
            }
        }
    }
    if(dis[n] == -1e17) return -1;
    else return dis[n];    
}
