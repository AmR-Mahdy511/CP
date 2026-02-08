struct dsu{
    vector < ll > group , parent , mx , mn;
    dsu(int n)
    {
        group.resize(n+1, 1) , parent.resize(n+1) , mx.resize(n+1) , mn.resize(n+1);
        for(int i = 0 ; i <= n ; i++) parent[i] = i;
        mx = mn = parent;
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
            mx[leader2] = max( mx[leader2] , mx[leader1] );
            mn[leader2] = min( mn[leader2] , mn[leader1] );
        }
        else
        {
            group[leader1] += group[leader2];
            parent[leader2] = parent[leader1];
            mx[leader1] = max( mx[leader2] , mx[leader1] );
            mn[leader1] = min( mn[leader2] , mn[leader1] );           
        }
    }
    ll getsize(ll node)
    {
        return group[find(node)];
    }
    void print(ll node)
    {
        ll leader = find(node);
        ll Max = mx[leader] , Min = mn[leader] , sz = group[leader];
        cout << Min << sp << Max << sp << sz << nl;
    }
};
