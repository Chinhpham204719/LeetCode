class Solution {
public:
    vector<bool> vis;
    vector<int> Nums;
    vector<int> graph[20007];
    vector<int> sz;
    void solve(int u){
        sz[u] = Nums[u];
        vis[u] = true;
        for(auto v:graph[u]){
            if(vis[v])continue;
            solve(v);
            sz[u]+=sz[v];
        }
    }
    
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        Nums = nums;
        vis.resize(n);
        sz.resize(n);
        // Create the graph with adjacent list
        for(int i = 0;i<edges.size();i++){
            int u = edges[i][0];
            int v = edges[i][1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        int ans = 0;
        
        // Dfs to get the weight of each subtree (well known algorithm)
        // The root does not matter
        solve(0);

        // Define W as the total weight of the tree
        int W = accumulate(nums.begin(),nums.end(),0);
        
        for(int x = 1;x*x<=W;x++){
            if(W%x ==0){
                // Check for every divisor
                int cont = 0;
                for(int j = 0;j<n;j++){
                    // Count every subtree with weight multiple of x
                    if(sz[j]%x ==0){
                        cont++;
                    }
                }
                int k = W/x;
                // Check the condition that must be exactly W/x components and update the answer
                // To make k components in a tree we need to erase k-1 edges 
                if(cont == k )
                    ans = max(ans,k-1);
                
                if((W/x)==x)continue;

                // The same for the other divisor W/x
                int otherDiv = W/x;
                cont = 0;
                for(int j = 0;j<n;j++){
                    if(sz[j]%otherDiv==0){
                        cont++;
                    }
                }
                k = W/otherDiv;
                if(cont==k)
                    ans = max(ans,k-1);
            }
        }
        return ans;
        
    }
};
