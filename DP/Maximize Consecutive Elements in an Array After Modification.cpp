class Solution {
public:
    int ans = 0;
    int dp[1000005];
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = 1; i <= nums.size(); i++){
            dp[nums[i-1]+1] = max(1, dp[nums[i-1]]+1);
            dp[nums[i-1]] = max(1, dp[nums[i-1]-1]+1);
            ans = max(ans, dp[nums[i-1]]);
            ans = max(ans, dp[nums[i-1]+1]);
        }
        return ans;
    }
};
