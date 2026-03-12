#include <bits/stdc++.h>
using namespace std;

// ---------- Graph ----------
vector< vector<int> > adj; // adjacency list
vector< int > vis;         // vis
vector< int > color;       // for cycle detection
vector< int > topo;        // for topological sort


// ---------- DFS ----------
void dfs(int u)
{
    vis[u] = 1;
    for(auto &it : adj[u])
    {
        if( !vis[it] ) dfs(it);
    }
}

function < void (int) > dfs = [&](int node) -> void
{
    vis[node] = 1;
    for(auto &it : adj[node])
    {
        if( !vis[it] ) dfs(it);
    }
};


// ---------- Count Nodes in Component ----------
int dfs_count(int u)
{
    vis[u] = 1;
    int cnt = 1;

    for(auto &it : adj[u])
    {
        if( !vis[it] ) cnt += dfs_count(it);
    }

    return cnt;
}

function < int (int) > dfs_count = [&](int node) -> int
{
    vis[node] = 1;
    int cnt = 1;

    for(auto &it : adj[node])
    {
        if( !vis[it] )
        {
            cnt += dfs_count(it);
        }
    }

    return cnt;
};


// ---------- Number of Connected Components ----------
int comp = 0;

function < int (int) > dfs_comp = [&](int node) -> int
{
    vis[node] = 1;
    int cnt = 1;

    for(auto &it : adj[node])
    {
        if( !vis[it] )
        {
            cnt += dfs_comp(it);
        }
    }

    return cnt;
};

// usage
/*
for(int i = 1 ; i <= n ; i++)
{
    if( !vis[i] )
    {
        dfs_comp(i);
        comp++;
    }
}
*/
// ---------- Max size of biggest Connected Component ----------
function < int (int) > dfs_comp = [&](int node) -> int
{
    vis[node] = 1;
    int cnt = 1;
     
    for(auto &it : adj[node])
       {
                if( !vis[it] )
        {
                cnt += dfs_comp(it);
        }
    }
     
    return cnt;
};
int Max = 0;
for(int i = 1 ; i <= n ; i++) if( !vis[i] ) Max = max( Max , dfs_comp(i) );

// ---------- Detect Cycle in Directed Graph ----------
bool dfs_cycle(int u)
{
    color[u] = 1; // gray

    for(auto &it : adj[u])
    {
        if( color[it] == 0 )
        {
            if( dfs_cycle(it) ) return 1;
        }
        else if( color[it] == 1 ) return 1;
    }

    color[u] = 2; // black
    return 0;
}

function < bool (int) > dfs_cycle = [&](int node) -> bool
{
    color[node] = 1;

    for(auto &it : adj[node])
    {
        if( color[it] == 0 )
        {
            if( dfs_cycle(it) ) return 1;
        }
        else if( color[it] == 1 ) return 1;
    }

    color[node] = 2;
    return 0;
};


// ---------- Topological Sort ----------
void dfs_topo(int u)
{
    vis[u] = 1;

    for(auto &it : adj[u])
    {
        if( !vis[it] ) dfs_topo(it);
    }

    topo.push_back(u);
}

function < void (int) > dfs_topo = [&](int node) -> void
{
    vis[node] = 1;

    for(auto &it : adj[node])
    {
        if( !vis[it] ) dfs_topo(it);
    }

    topo.push_back(node);
};


// ---------- DFS on Grid ----------
int dx[4] = {0 , 1 , 0 , -1};
int dy[4] = {1 , 0 , -1 , 0};

bool is_valid(int x , int y , vector< vector<int> > &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    if( x < 0 || y < 0 || x >= n || y >= m || grid[x][y] == 1 )
        return 0;

    return 1;
}

void dfs_grid(int x , int y , vector< vector<int> > &grid)
{
    if( !is_valid(x , y , grid) ) return;

    grid[x][y] = 1;

    for(int d = 0 ; d < 4 ; d++)
    {
        dfs_grid(x + dx[d] , y + dy[d] , grid);
    }
}

function < void (int , int , vector< vector<int> >& ) > dfs_grid = [&](int x , int y , vector< vector<int> > &grid) -> void
{
    if( !is_valid(x , y , grid) ) return;

    grid[x][y] = 1;

    for(int d = 0 ; d < 4 ; d++)
    {
        dfs_grid(x + dx[d] , y + dy[d] , grid);
    }
};


// ---------- Cycle in Undirected Graph ----------
bool dfs_cycle_undirected(int u , int p)
{
    vis[u] = 1;

    for(auto &it : adj[u])
    {
        if( !vis[it] )
        {
            if( dfs_cycle_undirected(it , u) ) return 1;
        }
        else if( it != p ) return 1;
    }

    return 0;
}

function < bool (int , int) > dfs_cycle_undirected = [&](int node , int par) -> bool
{
    vis[node] = 1;

    for(auto &it : adj[node])
    {
        if( !vis[it] )
        {
            if( dfs_cycle_undirected(it , node) ) return 1;
        }
        else if( it != par ) return 1;
    }

    return 0;
};
