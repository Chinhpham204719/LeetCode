class Solution {
private:
    void findPrimes(vector<vector<int>>& primes){
        for(int i = 1; i <= 50; i++){
            for(int j = 1; j <= 50; j++){
                int gcd = __gcd(i, j);
                if(gcd == 1)
                    primes[i].push_back(j);
            }
        }
    }

    void dfs(int node, int parent, vector<int>& values, vector<int>& coprimes, 
                vector<vector<int>>& primes, vector<vector<int>>& depth, 
                    int height, vector<int> adj[]){

        int coprimeNodeDepth = -1;
        for(auto prime: primes[values[node]]){
            if(depth[prime][0] > coprimeNodeDepth){
                coprimeNodeDepth = depth[prime][0];
                coprimes[node] = depth[prime][1];
            }
        }

        vector<int> currDepth = depth[values[node]];

        depth[values[node]] = {height, node};
        for(auto adjNode: adj[node]){
            if(adjNode != parent){
                dfs(adjNode, node, values, coprimes, primes, depth, height + 1, adj);
            }
        }

        depth[values[node]] = currDepth;
    }
public:
    vector<int> getCoprimes(vector<int>& values, vector<vector<int>>& edges) {
        int n = values.size();

        vector<int> adj[n+1];
        for(auto it: edges){
            int u = it[0], v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<vector<int>> primes(51);
        findPrimes(primes);

        vector<int> coprimes(n, -1);

        // {nodeValues, {depth, node}}
        vector<vector<int>> depth(51, vector<int> (2, -1));
        dfs(0, -1, values, coprimes, primes, depth, 0, adj);

        return coprimes;
    }
};
