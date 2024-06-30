class Solution {
    int MOD = 1e9 + 7; 
    int dp[10004][21]; 
    int recursive(int n,int k){ 
        if(k == 0) return 1; // this is a valid way of distribution
        if(n == 0) return 0; 
        if(dp[n][k] != -1) return dp[n][k]; 
        return dp[n][k] = (recursive(n,k-1) + recursive(n-1,k))%MOD;
    }
public:
    vector<int> waysToFillArray(vector<vector<int>>& queries) {
        for(int i=0;i<10004;i+=1) for(int j=0;j<21;j+=1) dp[i][j] = -1; recursive(10003,20); 
        vector<int> res; 
        for(auto &q: queries){
            int n = q[0]; 
            int k = q[1]; 
            // find prime factorizatio of k then work forward 
            map<int,int> mp; 
            for(int i=2;i*i<=k;i+=1){
                while(q[1]%i == 0) q[1]/=i,mp[i] += 1; 
            }
            if(q[1] != 1) mp[q[1]] += 1; 
            long long ans = 1; 
            for(auto &[elm,freq]: mp){
                ans *= dp[n][freq]; 
                ans %= MOD; 
            }
            res.push_back(ans); 
        }
        return res;
    }
};
