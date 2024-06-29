class Solution {
public:
    int modin(int x){
        int k = 1e9+5, mod = 1e9+7,ans = 1;
        while(k){
            if(k&1){
                ans = (ans*1LL*x)%mod;
            }
            x = (x*1LL*x)%mod;
            k >>= 1;
        }
        return ans;
    }
    int countAnagrams(string s) {
        int ans = 1, mod = 1e9+7,k;
        int n = s.length(),i;
        vector<int> dp(n+1,1);
        for(i = 2; i <= n; i++){
            dp[i] = (i*1LL*dp[i-1])%mod;
        }
        vector<int> v(26,0);
        int x = 0;
        for(auto &i: s){
            if(i==' '){
                k = dp[x];
                for(auto &j: v){
                    if(j>1)
                        k = (k*1LL*modin(dp[j]))%mod;
                }
                ans = (ans*1LL*k)%mod;
                // cout<<ans<< " ";
                fill(v.begin(),v.end(),0);
                x = 0;
            }else{
                x++;
                v[i-'a']++;
            }
        }
        // cout<<"#";
                k = dp[x];
                for(auto &j: v){
                    if(j>1)
                        k = (k*1LL*modin(dp[j]))%mod;
                }
                ans = (ans*1LL*k)%mod;
        // cout<<ans;
        
        return ans;
    }
};
