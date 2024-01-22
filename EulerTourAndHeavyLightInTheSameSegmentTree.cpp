/*
 * This code implements hld and ett in the same Segment Tree
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX_N=1e5;
int pos[MAX_N],heavy[MAX_N],subtree[MAX_N],depth[MAX_N],head[MAX_N],par[MAX_N],cur_pos;

void init(int n)
{
    for(int i=0;i<n;++i)
    {
        pos[i]=heavy[i]=-1;
        subtree[i]=depth[i]=0;
        head[i]=par[i]=i;
    }
    cur_pos=0;
}

void dfs(int node,int parent,vector<int> adj[])
{
    subtree[node]=1;
    int idx=-1;
    for(int i=0;i<adj[node].size();++i)
    {
        int v=adj[node][i];
        if(v!=parent)
        {
            depth[v]=depth[node]+1;
            par[v]=node;
            dfs(v,node,adj);
            subtree[node]+=subtree[v];
            if(heavy[node]==-1)
            {
                heavy[node]=v;
                idx=i;
            }
            else
            {
                if(subtree[heavy[node]]<subtree[v])
                {
                    heavy[node]=v;
                    idx=i;
                }
            }
        }
    }
    if(idx!=-1)     // Make sure that the heavy node is the 1st node in the adj list. This way the position of the node in the hld array will coincide with the position in ett array
    {
        swap(adj[node][0],adj[node][idx]);
    }
}

void hld(int node,int chain,vector<int> adj[])      // After ensuring that the 1st node in the adj list of the node is the heavy child, pre[i] coincides with pos[i] and post[i] coincides with pos[i]+subtree[i]-1
{
    head[node]=chain;
    pos[node]=cur_pos++;
    if(heavy[node]!=-1)
    {
        hld(heavy[node],chain,adj);
    }
    for(auto &v:adj[node])
    {
        if(v!=par[node]&&v!=heavy[node])
        {
            hld(v,v,adj);
        }
    }
}

class SegmentTree  // range sum update range max query
{
    
private:
    
    vector<pair<int,int>> seg;  // {sum,max}
    vector<int> lazy;
    
public:

    SegmentTree(int n)
    {
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }
    
    void update(int ind,int lo,int hi,int l,int r,int val)
    {
        if(lazy[ind]!=0)
        {
            seg[ind].first+=(hi-lo+1)*lazy[ind];
            seg[ind].second+=lazy[ind];
            if(lo!=hi)
            {
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }
        if(l>hi||lo>r)
        {
            return;
        }
        if(l<=lo&&hi<=r)
        {
            seg[ind].first+=(hi-lo+1)*val;
            seg[ind].second+=val;
            if(lo!=hi)
            {
                lazy[2*ind+1]+=val;
                lazy[2*ind+2]+=val;
            }
            return;
        }
        int mid=lo+(hi-lo)/2;
        update(2*ind+1,lo,mid,l,r,val);
        update(2*ind+2,mid+1,hi,l,r,val);
        seg[ind].first=seg[2*ind+1].first+seg[2*ind+2].first;
        seg[ind].second=max(seg[2*ind+1].second,seg[2*ind+2].second);
    }
    
    pair<int,int> query(int ind,int lo,int hi,int l,int r)
    {
        if(lazy[ind]!=0)
        {
            seg[ind].first+=(hi-lo+1)*lazy[ind];
            seg[ind].second+=lazy[ind];
            if(lo!=hi)
            {
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }
        if(l>hi||lo>r)
        {
            return {0,-1e9};
        }
        if(l<=lo&&hi<=r)
        {
            return seg[ind];
        }
        int mid=lo+(hi-lo)/2;
        pair<int,int> left=query(2*ind+1,lo,mid,l,r),right=query(2*ind+2,mid+1,hi,l,r),ans;
        ans.first=left.first+right.first;
        ans.second=max(left.second,right.second);
        return ans;
    }
    
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,q;
    cin>>n;
    init(n);
    SegmentTree st(n);
    vector<int> adj[n];
    for(int i=1;i<n;++i)
    {
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0,0,adj);
    hld(0,0,adj);
    cin>>q;
    while(q--)
    {
        string choice;
        cin>>choice;
        if(choice[0]=='a')  // pre[u] will coincide with pos[u] and post[u] will coincide with pos[u]+subtree[u]-1
        {
            int u,x;
            cin>>u>>x;
            u--;
            st.update(0,0,n-1,pos[u],pos[u]+subtree[u]-1,x);
        }
        else  // appliying hld query normally
        {
            int u,v,ans=-1e9;
            cin>>u>>v;
            u--;
            v--;
            while(head[u]!=head[v])
            {
                if(depth[head[u]]<depth[head[v]])
                {
                    swap(u,v);
                }
                ans=max(ans,st.query(0,0,n-1,pos[head[u]],pos[u]).second);
                u=par[head[u]];
            }
            if(depth[u]<depth[v])
            {
                swap(u,v);
            }
            ans=max(ans,st.query(0,0,n-1,pos[v],pos[u]).second);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
