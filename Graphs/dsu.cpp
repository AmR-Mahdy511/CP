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
