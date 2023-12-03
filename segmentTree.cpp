//Segment Tree class
/*
  The default segment tree here is implementing range sum updates using lazy propogation
  The build function builds the segment tree according to the given array
  The update function adds the value 'val' to all the array elements from queryLow to queryHigh
  The query function returns the sum of the values of the array for arrLow to arrHigh
*/
class SegmentTree       
{

private:

    vector<long long> segmentTree;
    vector<long long> lazy;

public:

    SegmentTree(long long n)
    {
        segmentTree.resize(4*n+1);
        lazy.resize(4*n+1,0);
    }

    void build(long long segInd,long long arrLow,long long arrHigh,vector<long long> &arr)
    {
        if(arrHigh==arrLow)
        {
            segmentTree[segInd]=arr[arrHigh];
            return ;
        }
        long long mid=arrLow+(arrHigh-arrLow)/2;
        build(2*segInd+1,arrLow,mid,arr);
        build(2*segInd+2,mid+1,arrHigh,arr);
        segmentTree[segInd]=segmentTree[2*segInd+1]+segmentTree[2*segInd+2];
    }

    void update(long long segInd,long long arrLow,long long arrHigh,long long queryLow,long long queryHigh,long long val)
    {
        if(lazy[segInd]!=0)
        {
            segmentTree[segInd]+=(arrHigh-arrLow+1)*lazy[segInd];
            if(arrLow!=arrHigh)
            {
                lazy[2*segInd+1]+=lazy[segInd];
                lazy[2*segInd+2]+=lazy[segInd];
            }
            lazy[segInd]=0;
        }
        if(arrHigh<queryLow||arrLow>queryHigh)
        {
            return ;
        }
        if(queryLow<=arrLow&&arrHigh<=queryHigh)
        {
            segmentTree[segInd]+=(arrHigh-arrLow+1)*val;
            if(arrHigh!=arrLow)
            {
                lazy[2*segInd+1]+=val;
                lazy[2*segInd+2]+=val;
            }
            return ;
        }
        long long mid=arrLow+(arrHigh-arrLow)/2;
        update(2*segInd+1,arrLow,mid,queryLow,queryHigh,val);
        update(2*segInd+2,mid+1,arrHigh,queryLow,queryHigh,val);
        segmentTree[segInd]=segmentTree[2*segInd+1]+segmentTree[2*segInd+2];
    }

    long long query(long long segInd,long long arrLow,long long arrHigh,long long queryLow,long long queryHigh)
    {
        if(lazy[segInd]!=0)
        {
            segmentTree[segInd]+=(arrHigh-arrLow+1)*lazy[segInd];
            if(arrLow!=arrHigh)
            {
                lazy[2*segInd+1]+=lazy[segInd];
                lazy[2*segInd+2]+=lazy[segInd];
            }
            lazy[segInd]=0;
        }
        if(arrHigh<queryLow||arrLow>queryHigh)
        {
            return 0;
        }
        if(queryLow<=arrLow&&arrHigh<=queryHigh)
        {
            return segmentTree[segInd];
        }
        long long mid=arrLow+(arrHigh-arrLow)/2;
        long long left=query(2*segInd+1,arrLow,mid,queryLow,queryHigh),right=query(2*segInd+2,mid+1,arrHigh,queryLow,queryHigh);
        return left+right;
    }

};
