void dijkstra(int src,vector<pair<int,int>> adj[],vector<int> &dist)
{
    set<pair<int,int>> st;
    dist[src]=0;
    st.insert({0,src});
    while(st.size())
    {
        auto it=st.begin();
        int node=it->second,dis=it->first;
        st.erase(it);
        for(auto &v:adj[node])
        {
            int curNode=v.first,curDist=v.second;
            if(dist[curNode]>dis+curDist)
            {
                if(dist[curNode]!=1e9)
                {
                    st.erase({dist[curNode],curNode});
                }
                dist[curNode]=dis+curDist;
                st.insert({dist[curNode],curNode});
            }
        }
    }
}
