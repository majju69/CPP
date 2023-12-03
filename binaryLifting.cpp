#include <bits/stdc++.h>
using namespace std;

const int LOG=21;
const int MAX_N=100000;
int up[MAX_N][LOG],depth[MAX_N];

/*
 * Finds all the ancestors of all nodes that are a power of 2
*/

void dfs(int node,vector<int> adj[],vector<bool> &vis)
{
    vis[node]=true;
    for(auto &v:adj[node])
    {
        if(!vis[v])
        {
            up[v][0]=node;      // Setting the (2^0)th ancestor i.e. the 1st ancestor to the parent
            depth[v]=depth[node]+1;     // Setting depth[node]=depth[par]+1
            for(int j=1;j<LOG;++j)      // Setting the (2^j)th ancestor as (2^(j-1))th ancestor of the (2^(j-1))th ancestor
            {
                up[v][j]=up[up[v][j-1]][j-1];
            }
            dfs(v,adj,vis);     // Calling dfs to recursively set all the nodes' ancestors
        }
    }
}

int main()
{
    int n,k,node;
    cin>>n>>k>>node;
    vector<int> adj[n];
    vector<bool> vis(n,false);
    for(int i=0;i<n-1;++i)      // Taking the graph as an input
    {
        int u,v;
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    depth[0]=0;     // Setting the depth of root to 0
    for(int j=0;j<LOG;++j)      // Setting all the ancestors of the root to the root itself
    {
        up[0][j]=0;
    }
    dfs(0,adj,vis);
    if(k>depth[node-1])
    {
        cout<<-1<<'\n';
    }
    else
    {
        int cur=node-1;
        for(int i=LOG-1;i>=0;--i)       // Breaking the number into binary and finding the numbers according to the powers of 2
        {
            if(k&(1<<i))
            {
                cur=up[cur][i];
            }
        }
        cout<<cur<<'\n';
    }
    return 0;
}
