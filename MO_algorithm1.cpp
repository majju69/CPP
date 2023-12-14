// MO algorithm to process q queries and for each query, displays the number of distinct elements in that range. This application doesn't support updates.
// If this doesn't work try declaring the blockSize as a constant globally according to the largest array size in the constraints

#include <bits/stdc++.h>
using namespace std;

struct query
{
    int index,left,right,block;
};

bool cmp(query q1,query q2)
{
    if(q1.block==q2.block)    // Try reversing the inequalities inside this in case of TLE
    {
        if(q1.block&1)
        {
            return q1.right<q2.right;
        }
        else
        {
            return q1.right>q2.right;
        }
    }
    return q1.block<q2.block;
}

// To add an element in this case, increase its freq. If the freq becomes 1, we found a new element and so increment the number of distinct elements by one

inline void addElement(int pos,vector<int> &a,vector<int> &freq,int &cnt)
{
    freq[a[pos]]++;
    if(freq[a[pos]]==1)
    {
        cnt++;
    }
}

// To remove an element, decrease its freq. If the freq becomes 0, we deleted the element completely and so decrement the number of distinct elements by one

inline void removeElement(int pos,vector<int> &a,vector<int> &freq,int &cnt)
{
    freq[a[pos]]--;
    if(freq[a[pos]]==0)
    {
        cnt--;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n,q,ind=0,l=0,r=-1,maxx=0,blockSize=0,cnt=0;
    map<int,int> mp;
    cin>>n>>q;
    vector<int> a(n),ans(q),freq;
    vector<query> queries(q);
    blockSize=sqrtl(n);     // block size of sqrt(n) is optimum
    for(auto &v:a)
    {
        cin>>v;
        mp[v]=0;
    }
    for(auto &v:mp)
    {
        v.second=ind++;
    }
    for(auto &v:a)
    {
        v=mp[v];
        maxx=max(maxx,v);
    }
    freq.resize(maxx+1);
    for(int i=0;i<q;++i)
    {
        int x,y;
        cin>>x>>y;
        queries[i].left=x-1;
        queries[i].right=y-1;
        queries[i].block=(x-1)/blockSize;
        queries[i].index=i;
    }
    sort(queries.begin(),queries.end(),cmp);
    // always add elements before removind i.e. write the while loop for adding the elements before the while loop for removing them. Otherwise the code may crash.
    for(auto &v:queries)
    {
        // In case of adding an element, first change the pointer and then add the element
        while(v.left<l)
        {
            l--;
            addElement(l,a,freq,cnt);
        }
        while(v.right>r)
        {
            r++;
            addElement(r,a,freq,cnt);
        }
        // In case of removing an element, first remove the element and then change the pointer
        while(v.left>l)
        {
            removeElement(l,a,freq,cnt);
            l++;
        }
        while(v.right<r)
        {
            removeElement(r,a,freq,cnt);
            r--;
        }
        ans[v.index]=cnt;
    }
    for(auto &v:ans)
    {
        cout<<v<<'\n';
    }
    return 0;
}
