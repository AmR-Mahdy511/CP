    /*
        Tree Diameter :
        For each node:
        - Height = 1 + Max child height
        - Diameter = max( best diameter from children , sum of two largest child heights )
        ans is -> Diameter(1,0).first
    */
  function< pair<int,int>(int,int) > Diameter = [&](int node , int par) -> pair<int,int>
    {
        int fi_Max = 0 , se_Max = 0;
        int cur_dia = 0;

        for( auto &child : adj[node] )
        {
            if( child == par ) continue;

            auto [ child_dia , child_h ] = Diameter( child , node );

            cur_dia = max( cur_dia , child_dia );

            if( child_h >= fi_Max )
            {
                se_Max = fi_Max;
                fi_Max = child_h;
            }
            else if( child_h > se_Max )
            {
                se_Max = child_h;
            }
        }
        int Max_diameter = max( cur_dia , fi_Max + se_Max ) , Max_height = fi_Max + 1;
        return {  Max_diameter , Max_height  };
    };
