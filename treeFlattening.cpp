#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
 * The dfs flattens the tree and converts it into an array such that the subtrees form consecutive segments
*/

void dfs(ll node,vector<ll> adj[],vector<bool> &vis,vector<ll> &pre,vector<ll> &value,vector<ll> &post,vector<ll> &a,ll &timer)
{
    vis[node]=true;
    pre[node]=timer;        // {The node i in the array corrsponds to pre[i] in the value_array on which we will operate}
    value[timer]=a[node];   // {                                                                                        }
    for(auto &v:adj[node])
    {
        if(!vis[v])
        {
            timer++;        // We increment the timer only when going down an edge
            dfs(v,adj,vis,pre,value,post,a,timer);
        }
    }
    post[node]=timer;       // The post number obtained in this dfs gives the index of the last vertex in the subtree of node in the value_array
}

class SegmentTree
{
    
private:
    
    vector<ll> seg;
    
public:
    
    SegmentTree(ll n)
    {
        seg.resize(4*n+1);
    }
    
    void build(ll ind,ll lo,ll hi,vector<ll> &value)
    {
        if(lo==hi)
        {
            seg[ind]=value[lo];
            return;
        }
        ll mid=lo+(hi-lo)/2;
        build(2*ind+1,lo,mid,value);
        build(2*ind+2,mid+1,hi,value);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    
    void update(ll ind,ll lo,ll hi,ll i,ll val)
    {
        if(lo==hi)
        {
            seg[ind]=val;
            return;
        }
        ll mid=lo+(hi-lo)/2;
        if(i<=mid)
        {
            update(2*ind+1,lo,mid,i,val);
        }
        else
        {
            update(2*ind+2,mid+1,hi,i,val);
        }
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    
    ll query(ll ind,ll lo,ll hi,ll l,ll r)
    {
        if(l>hi||lo>r)
        {
            return 0;
        }
        if(l<=lo&&hi<=r)
        {
            return seg[ind];
        }
        ll mid=lo+(hi-lo)/2;
        ll left=query(2*ind+1,lo,mid,l,r),right=query(2*ind+2,mid+1,hi,l,r);
        return left+right;
    }
    
};

int main()
{
    ll n,q,timer=0;
    cin>>n>>q;
    vector<ll> a(n),adj[n],pre(n),value(n),post(n);
    vector<bool> vis(n,false);
    for(auto &v:a)
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
    dfs(0,adj,vis,pre,value,post,a,timer);
    SegmentTree st(n);
    st.build(0,0,n-1,value);
    while(q--)
    {
        ll type;
        cin>>type;
        if(type==1)
        {
            ll i,val;
            cin>>i>>val;
            i=pre[i-1];
            st.update(0,0,n-1,i,val);
        }
        else
        {
            ll i,l=-1,r=-1;
            cin>>i;
            l=pre[i-1];
            r=post[i-1];
            cout<<st.query(0,0,n-1,l,r)<<'\n';
        }
    }
    return 0;
}
