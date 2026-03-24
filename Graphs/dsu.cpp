struct dsu{
    vector < ll > group , parent;
    dsu(int n)
    {
        group.resize(n+1, 1) , parent.resize(n+1);
        for(int i = 0 ; i <= n ; i++) parent[i] = i;
    }
    ll find(ll node)
    {
        if(parent[node] == node) return node;
        return parent[node] = find(parent[node]);
    }
    bool samegroup(ll fi_node , ll se_node)
    {
        return find(fi_node) == find(se_node);
    }
    void merge(ll fi_node, ll se_node)
    {
        ll leader1 = find(fi_node);
        ll leader2 = find(se_node);
        if(leader1 == leader2) return;
        if(group[leader1] < group[leader2])
        {
            group[leader2] += group[leader1];
            parent[leader1] = parent[leader2];
        }
        else
        {
            group[leader1] += group[leader2];
            parent[leader2] = parent[leader1];
        }
    }
    ll getsize(ll node)
    {
        return group[find(node)];
    }
};
// =================================================================================================================================================== //
struct dsu{
    vector < int > parent;
    dsu(int n) { parent.assign( n + 1 , - 1); }

    int find( int u )
    {
        if( parent[u] < 0 ) return u;
        return parent[u] = find(parent[u]);
    }
    int same_group( int u , int v ) { return find(u) == find(v); }
    int get_size( int u ){ return -parent[find(u)]; }
    bool merge( int u , int v )
    {
        int fi_leader = find(u) , sec_leader = find(v);
        if( fi_leader == sec_leader ) return 0;
        
        // fi leader is bigger than sec
        if( -parent[fi_leader] < -parent[sec_leader] ) swap( fi_leader , sec_leader );
        parent[fi_leader] += parent[sec_leader];
        parent[sec_leader] = fi_leader;
        return 1; 
    }
};
