const int MOD = 1e9 + 7;
int dp[9 * 24][24][2];
class Solution {
public:
    int helper(string &s, int mn, int mx, int sum, int ind, bool tight){
        if(sum > mx)return 0;
        if(ind == s.length()) return sum >= mn;
        if(dp[sum][ind][tight] != -1)return dp[sum][ind][tight];
        int ans = 0;
        int d = tight?(s[ind] - '0'):9;
        for(int i = 0; i <= d; i++)
            ans = ((ans%MOD) + (helper(s, mn, mx, sum + i, ind + 1, (tight && (i == d)))%MOD))%MOD;
        return dp[sum][ind][tight] = ans%MOD;
    }
    int count(string num1, string num2, int min_sum, int max_sum) {
        memset(dp, -1, sizeof dp);
        long long ans = helper(num2, min_sum, max_sum, 0, 0, true);
        memset(dp, -1, sizeof dp);
        ans -= helper(num1, min_sum, max_sum, 0, 0, true);

        int sum = 0;
        for(auto i : num1)sum += (i - '0');
        if(sum >= min_sum && sum <= max_sum)ans++;

        return (ans + MOD)%MOD;
    }
};
