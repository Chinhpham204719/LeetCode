class Solution {
public:
    int dp[101][101];
    int pre[101];
    int func(int i,int k,vector<int>&houses) {
        if(i >= houses.size()) {
            if(k == 0) {
                return 0;
            }
            else return 1e9;
        }
        if(k == 0) return 1e9;
        if(dp[i][k] != -1) return dp[i][k];
        int ans = 1e9;
        for(int j = i; j < houses.size(); j++) {
            int dis = j - i + 1, med = 0,in = i + (j - i)/2;;
            if(dis%2 == 0) {
                int cost = pre[j] - pre[in];
                cost -= (pre[in]);
                if(i > 0) cost += pre[i-1];
                ans = min(ans, cost + func(j+1,k-1,houses));
                
            }
            else {
                med = houses[in];
                int cost = pre[j] - pre[in];
                cost -= (pre[in]);
                if(i > 0) cost += pre[i-1];
                cost += houses[in];
                ans = min(ans, cost + func(j+1,k-1,houses));
            }
        }
        return dp[i][k] =  ans;
    } 
    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(),houses.end());
        memset(dp,-1,sizeof(dp));
        memset(pre,0,sizeof(pre));
        pre[0] = houses[0];
        for(int i = 1; i<houses.size(); i++) pre[i] = pre[i-1] + houses[i];
        return func(0,k,houses);
    }
};
