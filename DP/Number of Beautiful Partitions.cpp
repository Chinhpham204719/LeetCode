class Solution {
public:
    int mod;
int solve(string &str,int k,int m,int n,vector<vector<int>> &dp,int i){
    if(k<0 || n-i < m*k)return 0;
    if(i>=n){
        if(k==0)return 1;
        return 0;
    }
    if(dp[i][k] != -1){
        return dp[i][k];
    }
    int a = 0;
    for(int j = i+m-1; j < n && j < n-(k-1)*m; j++){
        if((str[i]=='2'||str[i]=='3'||str[i]=='5'||str[i]=='7')&&(str[j]=='1'||str[j]=='4'||str[j]=='6'||str[j]=='8'||str[j]=='9')){
            a = (solve(str,k-1,m,n,dp,j+1)*1LL+a)%mod;
        }
    }
    return dp[i][k] = (a%mod);
}
    int beautifulPartitions(string s, int k, int m) {
        int n = s.length();
        mod = 1e9+7;
        vector<vector<int>> dp(n+1,vector<int>(k+1,-1));
        int a = solve(s,k,m,n,dp,0);
        return a;
    }
};
