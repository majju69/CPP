#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl '\n'
#define ll long long

#define f(i,n) for(long long i=0;i<n;i++)
#define rep(i,a,b) for(long long i=a;i<b;i++)
#define vll vector<long long> 
#define pll pair<long long,long long>
#define dll deque<long long>
#define all(x) x.begin(),x.end()
#define mp(a,b) make_pair(a,b)
#define pb(x) push_back(x)
#define input(arr,size) for(long long i=0;i<size;i++){long long item;cin>>item;arr.push_back(item);}
#define display(arr) for(auto v:arr){cout<<v<<' ';}cout<<endl;
#define ss second
#define ff first
#define isSetBit(a,i) (a&(1<<i))
#define setBit(a,i) (a|(1<<i))
#define unsetBit(a,i) (a&(~(1<<i)))
#define switchBit(a,i) (a^(1<<i))
#define countSetBits(a) __builtin_popcountll(a)
#define INF 1000000000000000010
#define MOD 1000000007
#define yes cout<<"YES\n"
#define no cout<<"NO\n"


//=================================================================================================================================
//debugger

#ifndef ONLINE_JUDGE
#define debug(a0) cerr << #a0 <<' '; _print(a0); cerr << endl;
#define debug2(a0,a1) cerr << #a0 <<' '; _print(a0); cerr << endl;cerr << #a1 <<' '; _print(a1); cerr << endl;
#define debug3(a0,a1,a2) cerr << #a0 <<' '; _print(a0); cerr << endl;cerr << #a1 <<' '; _print(a1); cerr << endl;cerr << #a2 <<' '; _print(a2); cerr << endl;
#define debug4(a0,a1,a2,a3) cerr << #a0 <<' '; _print(a0); cerr << endl;cerr << #a1 <<' '; _print(a1); cerr << endl;cerr << #a2 <<' '; _print(a2); cerr << endl;cerr << #a3 <<' '; _print(a3); cerr << endl;
#define debug5(a0,a1,a2,a3,a4) cerr << #a0 <<' '; _print(a0); cerr << endl;cerr << #a1 <<' '; _print(a1); cerr << endl;cerr << #a2 <<' '; _print(a2); cerr << endl;cerr << #a3 <<' '; _print(a3); cerr << endl;cerr << #a4 <<' '; _print(a4); cerr << endl;
#else
#define debug(a0) 
#define debug2(a0,a1) 
#define debug3(a0,a1,a2) 
#define debug4(a0,a1,a2,a3) 
#define debug5(a0,a1,a2,a3,a4) 
#endif

void _print(long long t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(long double t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(unsigned long long t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(deque <T> v);
template <class T> void _print(set <T> v);
template <class T> void _print(unordered_set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T, class V> void _print(unordered_map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.first); cerr << ","; _print(p.second); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(deque <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(unordered_set <T> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(unordered_map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

//=================================================================================================================================


//=================================================================================================================================
// Disjoint Set class

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

//=================================================================================================================================

//=================================================================================================================================
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

//=================================================================================================================================

vector<bool> isPrime(1000011,true);
//ll dp[10000][10000];              // Use these array only in questions using DP. Avoid using vectors
//ll arr;
vector<long long> ARR(1000011,0);
vector<vector<long long>> divisors(1000011);
vector<long long> FACT(21);
vector<long long> factMod(1000011);
vector<long long> bookShelf(1000011,0);

void fillFactMod()
{
    factMod[0]=1;
    for(long long i=0;i<factMod.size();++i)
    {
        if(i)
        {
            factMod[i]=(i*factMod[i-1])%MOD;
        }
    }
}

void fillFact()
{
    FACT[0]=1;
    for(long long i=0;i<FACT.size();++i)
    {
        if(i==0)
        {
            continue;
        }
        else
        {
            FACT[i]=i*FACT[i-1];
        }
    }
}

void sieve()
{
    isPrime[0]=isPrime[1]=false;
    isPrime[2]=true;
    for(long long p=2;p*p<1000011;p++)
    {
        if(isPrime[p]==true)
        {
            for(long long i=p*p;i<1000011;i+=p)
            {
                isPrime[i]=false;
            }
        }
    }
}

void fillDivisors()
{
    divisors[0].push_back(0);
    divisors[1].push_back(1);
    for(long long i=2;i<=1000011;i++)
    {
        divisors[i].push_back(1);
    }
    for(long long i=2;i<=1000011;i++)
    {
        for(long long j=i;j<=1000011;j+=i)
        {
            divisors[j].push_back(i);
        }
    }
}

long long gcd(long long a,long long b)
{
    return ((b==0)?a:gcd(b,a%b));
}

bool is_prime(long long n)
{
    if(n==1||n==0)
    {
        return false;
    }
    else if(n==2||n==3)
    {
        return true;
    }
    else
    {    
        for(long long i=2;i*i<=n;i++)
        {    
            if(n%i==0)
            {
                return false;
            }
        }
        return true;
    }
}

long long Multiply(long long a,long long b)        
{
    long long ans=0;
    a=a%INF;
    while(b)
    {
        if(b&1)
        {
            ans=(ans+a)%INF;
        }
        a=(a+a)%INF;       
        b>>=1;
    }
    return ans;
}


long long powINF(long long a,long long b)        
{
    long long ans=1;
    a=a%INF;
    while(b)
    {
        if(b&1)
        {
            ans=(Multiply(ans,a))%INF;
        }
        a=(Multiply(a,a))%INF;       
        b>>=1;
    }
    return ans;
}

long long powMOD(long long a,long long b)        // Use when MOD is of order 10^9 or less
{
    long long ans=1;
    a=a%MOD;
    while(b)
    {
        if(b&1)
        {
            ans=(ans*a)%MOD;
        }
        a=(a*a)%MOD;       
        b>>=1;
    }
    return ans;
}

long long nCrModPFermat(long long n,long long r)         // Ensure that fillFactMod() is called before this function is used
{
    if(n<r)
    {
        return 0;
    }
    if(r==0||r==n)
    {
        return 1;
    }
    return (factMod[n]*powMOD(factMod[r],MOD-2)%MOD*powMOD(factMod[n-r],MOD-2)%MOD)%MOD;
}

void countSort(vector<long long> &arr)
{
    vector<long long> ans;
    long long Max=0;
    for(auto val:arr)
    {
        bookShelf[val]++;
        if(val>Max)
        {
            Max=val;
        }
    }
    for(long long i=0;i<=Max;++i)
    {
        for(long long j=0;j<bookShelf[i];++j)
        {
            ans.push_back(i);
        }
    }
    arr=ans;
}

vector<long long> getPrefix(vector<long long> &a,bool startBy0=false)
{
    vector<long long> prefix;
    prefix.push_back(a[0]);
    for(long long i=1;i<a.size();++i)
    {
        prefix.push_back(a[i]+prefix.back());
    }
    if(startBy0)
    {
        reverse(prefix.begin(),prefix.end());
        prefix.push_back(0);
        reverse(prefix.begin(),prefix.end());
    }
    return prefix;
}

bool cmp(long long a,long long b)
{
    return (a>b);
}

// This is the main() for all your purposes
void* thread_function(void* arg) 
{
    FASTIO;
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("error.txt", "w", stderr);
    #endif
    auto aapkaSamayShuruHotaHaiAb=chrono::steady_clock::now();
    // sieve();
    // fillDivisors();
    // fillFact();
    // fillFactMod();
    long long Test_Case=1;
    cin>>Test_Case;
    for(long long TestCase=0;TestCase<Test_Case;++TestCase)
    {
        // memset(dp,-1,sizeof(dp));
        // cout<<"Case #"<<TestCase+1<<": ";
    }
    cout<<endl;
    auto samaySamampt=chrono::steady_clock::now();
    auto aapkaTotalTime=samaySamampt-aapkaSamayShuruHotaHaiAb;
    #ifndef ONLINE_JUDGE
        cerr << "\nTime : " << chrono::duration<double,milli>(aapkaTotalTime).count() << " ms\n";
    #endif
    return NULL;
}

int main() 
{
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // Set the stack size (in bytes) here.
    size_t stack_size=1024*1024*1024;   // Replace the 1st 1024 with how much MB you want the stack space
    pthread_attr_setstacksize(&attr, stack_size);
    if(pthread_create(&thread,&attr,thread_function,NULL)!=0) 
    {
        cerr<<"Error creating thread\n";
        return 1;
    }
    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);
    return 0;
}
