#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAX_N=2e5;
ll depth[MAX_N],head[MAX_N],pos[MAX_N],heavy[MAX_N],subTreeSize[MAX_N],par[MAX_N],timer;

class SegmentTree
{

private:
    
    vector<ll> seg;

public:

    SegmentTree(ll n)
    {
        seg.resize(4*n+1);
    }
    
    void build(ll ind,ll lo,ll hi,vector<ll> &a)
    {
        if(lo==hi)
        {
            seg[ind]=a[lo];
            return;
        }
        ll mid=lo+((hi-lo)>>1);
        build(2*ind+1,lo,mid,a);
        build(2*ind+2,mid+1,hi,a);
        seg[ind]=max(seg[2*ind+1],seg[2*ind+2]);
    }
    
    void update(ll ind,ll lo,ll hi,ll i,ll val)
    {
        if(lo==hi)
        {
            seg[ind]=val;
            return;
        }
        ll mid=lo+((hi-lo)>>1);
        if(i<=mid)
        {
            update(2*ind+1,lo,mid,i,val);
        }
        else
        {
            update(2*ind+2,mid+1,hi,i,val);
        }
        seg[ind]=max(seg[2*ind+1],seg[2*ind+2]);
    }

    ll query(ll ind,ll lo,ll hi,ll l,ll r)
    {
        if(l>hi||lo>r)
        {
            return -1e9;
        }
        if(l<=lo&&hi<=r)
        {
            return seg[ind];
        }
        ll mid=lo+((hi-lo)>>1);
        ll left=query(2*ind+1,lo,mid,l,r),right=query(2*ind+2,mid+1,hi,l,r);
        return max(left,right);
    }
    
};

void init(ll n)     //Initializing all the global arrays and timer
{
    for(ll i=0;i<n;++i)
    {
        depth[i]=0;
        head[i]=i;
        pos[i]=-1;
        heavy[i]=-1;
        subTreeSize[i]=0;
        par[i]=i;
        timer=0;
    }
}

// The heavy node is the node with tha max subtree size

void dfs(ll node,vector<ll> adj[],vector<bool> &vis)
{
    vis[node]=true;
    subTreeSize[node]=1;
    for(auto &v:adj[node])
    {
        if(!vis[v])
        {
            depth[v]=depth[node]+1;
            par[v]=node;
            dfs(v,adj,vis);
            subTreeSize[node]+=subTreeSize[v];
            if(heavy[node]==-1)
            {
                heavy[node]=v;
            }
            else
            {
                if(subTreeSize[heavy[node]]<subTreeSize[v])
                {
                    heavy[node]=v;
                }
            }
        }
    }
}

// Intially every node is given the chain number as itself. Then while calling hld, the heavy node is give the same chain number as the parent and all the other nodes are given the chain number as the node itself. The position of the node in the array for which the seg tree is build, is kept in pos[] array and that is the time at which hld() for thta particular node starts
    
void hld(ll node,ll chain,vector<ll> adj[],vector<bool> &vis,vector<ll> &value,vector<ll> &a)
{
    vis[node]=true;
    head[node]=chain;
    pos[node]=timer++;
    a[pos[node]]=value[node];
    if(heavy[node]!=-1)
    {
        hld(heavy[node],chain,adj,vis,value,a);
    }
    for(auto &v:adj[node])
    {
        if(v!=heavy[node]&&!vis[v])
        {
            hld(v,v,adj,vis,value,a);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,q;
    cin>>n>>q;
    vector<ll> value(n),a(n),adj[n];
    vector<bool> vis(n,false);
    init(n);
    for(auto &v:value)
    {
        cin>>v;
    }
    for(ll i=0;i<n-1;++i)
    {
        ll u,v;
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
    }
    dfs(0,adj,vis);
    for(ll i=0;i<n;++i)
    {
        vis[i]=false;
    }
    hld(0,0,adj,vis,value,a);
    SegmentTree st(n);
    st.build(0,0,n-1,a);
    while(q--)
    {
        ll type;
        cin>>type;
        if(type==1)
        {
            ll i,val;
            cin>>i>>val;
            i--;
            st.update(0,0,n-1,pos[i],val);
        }
        if(type==2)
        {
            ll u,v,ans=-1e9;
            cin>>u>>v;
            u--;
            v--;
            while(head[u]!=head[v])     // We compare the heads of the chains of the nodes till the head isn't equal
            {
                if(depth[head[u]]<depth[head[v]])
                {
                    swap(u,v);
                }
                ans=max(ans,st.query(0,0,n-1,pos[head[u]],pos[u]));     // As they are in different chains (as the head is different), we always need to calculate the ans (max in this case) from cur node to head
                u=par[head[u]];     // The one whose head has more depth (i.e. the one that has lower head) changes the chain to move up
            }
            if(depth[u]<depth[v])
            {
                swap(u,v);
            }
            ans=max(ans,st.query(0,0,n-1,pos[v],pos[u]));   // Now as both have same head, they belong to the same chain, so we just need to calculate ans (max in this case) between the two nodes
            cout<<ans<<' ';
        }
    }
    cout<<'\n';
    return 0;
}
