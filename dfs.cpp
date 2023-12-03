void dfs(int node,vector<int> adj[],vector<bool> &vis)
{
  vis[node]=true;
  for(auto &v:adj[node])
  {
    if(!vis[v])
    {
      dfs(v,adj,vis);
    }
  }
}
