class Solution {
public:

int n;
vector<int> pre;
long long dp[100005][2][2];

    vector<int> prefixSumArray(vector<int> &v)
    {
        int n = v.size();
        vector<int> ans(n);
        ans[0] = v[0];
        for (int i = 1; i < n; ++i)
            ans[i] = ans[i - 1] + v[i];
        return ans;
    }

    int f(vector<int> &v, int ind, int k, int x){
        if(dp[ind][k][x] != -1) return dp[ind][k][x];
        if(ind >= n-1) return dp[ind][k][x] = 0;
        long long sum = x == 1 ? v[ind+1] : pre[ind+1], ans = -1e9;
        if(!k) ans = 1e9;
        if(k) ans = max(f(v, ind+1, k, 1) + sum, f(v, ind+1, !k, 0) + sum);
        else ans = min(f(v, ind+1, k, 1) - sum, f(v, ind+1, !k, 0) - sum);
        return dp[ind][k][x] = ans;
    }

    int stoneGameVIII(vector<int>& v) {
        memset(dp, -1, sizeof(dp));
        n = v.size();
        pre = prefixSumArray(v);
        return f(v, 0, 1, 0);
    }
};
