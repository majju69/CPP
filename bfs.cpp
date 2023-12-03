void bfs(int node,vector<int> adj[],vector<bool> &vis)
{
    queue<int> a;
    q.push(node);
    vis[node]=true;
    while(q.size())
    {
        int curNode=q.front();
        q.pop();
        for(auto &v:adj[curNode])
        {
            if(!vis[v])
            {
                q.push(v);
                vis[v]=true;
            }
        }
    }
}
