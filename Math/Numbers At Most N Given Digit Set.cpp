class Solution {
public:
    int mod=1e9+7;
    int dp[32][2];
    int fun(int i,int tight,string& s,string &digit)
    {
        if(i==s.size())
            return 1;
        if(dp[i][tight]!=-1)
            return dp[i][tight];
        int ans=0;
        char mx='9';
        if(tight)
            mx=min(mx,s[i]);
        for(int j=0;j<digit.size() and digit[j]<=mx;j++)
            ans+=fun(i+1,(tight and digit[j]==mx)?1:0,s,digit);
        return dp[i][tight]=ans;
    }
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        int ans=0;
        string s=to_string(n);
        memset(dp,-1,sizeof(dp));
        string digit;
        for(auto it:digits)
            digit.push_back(it[0]);
        ans=fun(0,1,s,digit);
        for(int i=1;i<s.size();i++)
            ans+=fun(i,0,s,digit);
        return ans;
    }
};
