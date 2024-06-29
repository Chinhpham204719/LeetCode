class Solution {
public:
    set<int>prime;
    long long FinalAnswer;
    set<int> sieveOfEratosthenes(int n) {
        std::vector<bool> isPrime(n + 1, true);
        std::set<int> primes;

        isPrime[0] = isPrime[1] = false;  // 0 and 1 are not prime

        for (int p = 2; p * p <= n; ++p) {
            if (isPrime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    isPrime[i] = false;
                }
            }
        }

        for (int i = 2; i <= n; ++i) {
            if (isPrime[i]) {
                primes.insert(i);
            }
        }

        return primes;
    }
    int dfs1(int node,int parent,vector<int>adj[],vector<int>&record)
    {
        int total=0;
        int subTotal=0;
        for(auto &it:adj[node])
        {
            if (it==parent)
            {
                continue;
            }
            else
            {    
                long long tempTotal=dfs1(it,node,adj,record);
                total+=tempTotal;
                subTotal+=tempTotal*tempTotal;
            }
        }
        record[node]=total;
        if (prime.find(node)!=prime.end())
        {
            FinalAnswer+=(total*1ll*total-subTotal)/2;
            FinalAnswer+=total;
            return 0;
        }
        return total+1;
    }
    void dfs2(int node,int parent,vector<int>adj[],vector<int>&record,vector<int>&up)
    {
        bool flag=0;
        if (prime.find(node)!=prime.end())
        {
            // cout<<node<<" "<<record[node]+up[node]<<"\n";
            FinalAnswer+=up[node]+up[node]*record[node];
            flag=1;
        }
        for(auto &it:adj[node])
        {
            if (it==parent)
            {
                continue;
            }
            if (flag==1)
            {
                up[it]=0;
                dfs2(it,node,adj,record,up);
            }
            else if (prime.find(it)!=prime.end())
            {
                up[it]=record[node]+1+up[node];
                dfs2(it,node,adj,record,up);
            }
            else 
            {
                up[it]=up[node]+record[node]-record[it];
                dfs2(it,node,adj,record,up);
            }
        }
        
    }
    
    long long countPaths(int n, vector<vector<int>>& edges) 
    {
        prime=sieveOfEratosthenes(n);
        vector<int>adj[n+1];
        for(auto &it:edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        FinalAnswer=0;
        vector<int>record(n+1,0);
        dfs1(1,0,adj,record);
        vector<int>up(n+1,0);
        dfs2(1,0,adj,record,up);
        return FinalAnswer;
    }
};
