#include <bits/stdc++.h>
using namespace std;

// ---------- Graph ----------
vector< vector<int> > adj; // adjacency list
vector< int > vis;         // visited
vector< int > color;       // for cycle detection
vector< int > topo;        // for topological sort

// Basic DFS
void dfs(int u)
{
    vis[u] = 1;
    for(int v : adj[u]){
        if(!vis[v]) dfs(v);
    }
}

// Count nodes in component
int dfs_count(int u){
    vis[u] = 1;
    int cnt = 1;
    for(int v : adj[u]){
        if(!vis[v]) cnt += dfs_count(v);
    }
    return cnt;
}

// Detect cycle in directed graph
bool dfs_cycle(int u){
    color[u] = 1; // gray
    for(int v : adj[u]){
        if( color[v]==0 ) // white
        { 
            if(dfs_cycle(v)) return 1;
        }
        else if( color[v] == 1 ) return 1;
    }
    color[u] = 2; // black
    return 0;
}

// Topological sort (DFS)
void dfs_topo(int u){
    vis[u] = 1;
    for(int v : adj[u]){
        if(!vis[v]) dfs_topo(v);
    }
    topo.push_back(u); 
}

// ---------- DFS on Grid ----------
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

bool is_valid(int x, int y, vector<vector<int>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();
    if(x<0 || y<0 || x>=n || y>=m || grid[x][y]==1) return 0;
    return 1;
}

void dfs_grid(int x, int y, vector<vector<int>>& grid){
    if(!is_valid(x, y, grid)) return;

    grid[x][y] = 1; 

    for(int d = 0; d < 4; d++){
        dfs_grid(x + dx[d], y + dy[d], grid);
    }
}

// ---------- DFS on Undirected Graph ----------
bool dfs_cycle_undirected(int u, int p){
    vis[u] = 1;
    for(int v : adj[u])
    {
        if(!vis[v]){
            if(dfs_cycle_undirected(v,u)) return 1;
        } 
        else if(v != p) return 1; // found cycle
    }
    return 0;
}
