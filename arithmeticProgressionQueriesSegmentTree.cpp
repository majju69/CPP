#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline pair<ll,ll> add(pair<ll,ll> a,pair<ll,ll> b)
{
    return {a.first+b.first,a.second+b.second};
}

inline ll sum(ll lo,ll hi,pair<ll,ll> ap)
{
    ll n=hi-lo+1;
    return (2*ap.first*n+(n*n-n)*ap.second)/2;
}

class SegmentTree
{
    
private:

    vector<ll> seg;
    vector<pair<ll,ll>> lazy;
    
public:
    
    SegmentTree(ll n)
    {
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }
    
    void update(ll ind,ll lo,ll hi,ll l,ll r,pair<ll,ll> val)
    {
        if(lazy[ind].first!=0||lazy[ind].second!=0)
        {
            seg[ind]+=sum(lo,hi,lazy[ind]);
            if(lo!=hi)
            {
                pair<ll,ll> ap1,ap2;
                ap1=lazy[ind];
                ap2.first=lazy[ind].first+(1+(hi-lo)/2)*lazy[ind].second;
                ap2.second=lazy[ind].second;
                lazy[2*ind+1]=add(lazy[2*ind+1],ap1);
                lazy[2*ind+2]=add(lazy[2*ind+2],ap2);
            }
            lazy[ind]={0,0};
        }
        if(l>hi||lo>r)
        {
            return;
        }
        if(l<=lo&&hi<=r)
        {
            pair<ll,ll> ap;
            ap.first=val.first+(lo-l)*val.second;
            ap.second=val.second;
            seg[ind]+=sum(lo,hi,ap);
            if(lo!=hi)
            {
                pair<ll,ll> ap1,ap2;
                ap1=ap;
                ap2.first=ap.first+(1+(hi-lo)/2)*ap.second;
                ap2.second=ap.second;
                lazy[2*ind+1]=add(lazy[2*ind+1],ap1);
                lazy[2*ind+2]=add(lazy[2*ind+2],ap2);
            }
            return;
        }
        ll mid=lo+(hi-lo)/2;
        update(2*ind+1,lo,mid,l,r,val);
        update(2*ind+2,mid+1,hi,l,r,val);
        seg[ind]=seg[2*ind+1]+seg[2*ind+2];
    }
    
    ll query(ll ind,ll lo,ll hi,ll l,ll r)
    {
        if(lazy[ind].first!=0||lazy[ind].second!=0)
        {
            seg[ind]+=sum(lo,hi,lazy[ind]);
            if(lo!=hi)
            {
                pair<ll,ll> ap1,ap2;
                ap1=lazy[ind];
                ap2.first=lazy[ind].first+(1+(hi-lo)/2)*lazy[ind].second;
                ap2.second=lazy[ind].second;
                lazy[2*ind+1]=add(lazy[2*ind+1],ap1);
                lazy[2*ind+2]=add(lazy[2*ind+2],ap2);
            }
            lazy[ind]={0,0};
        }
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,q;
    cin>>n>>q;
    SegmentTree st(n);
    while(q--)
    {
        ll type;
        cin>>type;
        if(type==1)
        {
            ll l,r,a,d;
            pair<ll,ll> ap;
            cin>>l>>r>>a>>d;
            l--;
            r--;
            ap={a,d};
            st.update(0,0,n-1,l,r,ap);
        }
        else
        {
            ll i;
            cin>>i;
            i--;
            cout<<st.query(0,0,n-1,i,i)<<'\n';
        }
    }
    return 0;
}
