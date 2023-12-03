class DisjointSet 
{

private:

  vector<long long> ultimateParent,rank,size;

public:

  DisjointSet(long long n)
  {
      ultimateParent.resize(n+1);
      rank.resize(n+1,0);
      size.resize(n+1,1);
      for(long long i=0;i<=n;++i)
      {
          ultimateParent[i]=i;
      }
  }
  
  long long findUltimateParent(long long node)
  {
      if(ultimateParent[node]==node)
      {
          return node;
      }
      return ultimateParent[node]=findUltimateParent(ultimateParent[node]);
  }
  
  long long getSize(long long node)
  {
      return size[node];
  }
  
  long long getRank(long long node)
  {
      return rank[node];
  }
  
  void unionByRank(long long u,long long v)
  {
      long long ultimateParentOfU=findUltimateParent(u),ultimateParentOfV=findUltimateParent(v);
      if(ultimateParentOfU==ultimateParentOfV)
      {
          return ;
      }
      if(rank[ultimateParentOfU]<rank[ultimateParentOfV])
      {
          ultimateParent[ultimateParentOfU]=ultimateParentOfV;
      }
      else if(rank[ultimateParentOfU]>rank[ultimateParentOfV])
      {
          ultimateParent[ultimateParentOfV]=ultimateParentOfU;
      }
      else
      {
          ultimateParent[ultimateParentOfV]=ultimateParentOfU;
          rank[ultimateParentOfU]++;
      }
  }
  
  void unionBySize(long long u,long long v)
  {
      long long ultimateParentOfU=findUltimateParent(u),ultimateParentOfV=findUltimateParent(v);
      if(ultimateParentOfU==ultimateParentOfV)
      {
          return ;
      }
      if(size[ultimateParentOfU]<size[ultimateParentOfV])
      {
          ultimateParent[ultimateParentOfU]=ultimateParentOfV;
          size[ultimateParentOfV]+=size[ultimateParentOfU];
      }
      else
      {
          ultimateParent[ultimateParentOfV]=ultimateParentOfU;
          size[ultimateParentOfU]+=size[ultimateParentOfV];
      }
  }

};
