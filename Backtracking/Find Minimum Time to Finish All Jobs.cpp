class Solution {
public:
    void solve(int index, int n, vector<int> &jobs, vector<int> &dp, int &ans){
        if(index == n){
            ans = min(ans, *max_element(dp.begin(), dp.end()));
            return;
        }

        if(*max_element(dp.begin(),dp.end()) >= ans)
            return;

        for(int i = 0; i < dp.size(); i++){
            if(i > 0 and dp[i] >= dp[i - 1])continue;
            dp[i] += jobs[index];
            solve(index + 1, n, jobs, dp, ans);
            dp[i] -= jobs[index];
        }


    }
    int minimumTimeRequired(vector<int>& jobs, int k) {
        vector<int> dp(k);
        int ans = INT_MAX;
        int n = jobs.size();
        sort(jobs.begin(),jobs.end(),greater<int>());
        solve(0, n, jobs, dp, ans);
        return ans;
    }
};
