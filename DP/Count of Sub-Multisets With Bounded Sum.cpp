typedef long long ll;
const ll MOD = 1e9 + 7;

class Solution {
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        const ll N = 2e4;
        vector<ll> dp(N + 1);
        map<ll,ll> m;
        dp[0] = 1;
        m[0] = 1;
        for(auto x : nums) {
            m[x]++;
        }
        ll mult = m[0]; m.erase(0);
        for(auto x : m) {
            //{a, c}
            ll a = x.first;
            ll c = x.second;
            vector<ll> help(N + 1);
            for(int i = 1; i <= N; i++) {
                ll sum = 0;
                if(i - a >= 0) {
                    sum += dp[i-a];
                    sum += help[i-a];
                }
                if(i - a * (c + 1) >= 0) {
                    sum -= dp[i - a * (c + 1)];
                }
                help[i] = (sum + MOD) % MOD;
            }
            for(int i = 0; i <= N; i++) {
                dp[i] += help[i];
                if(dp[i] >= MOD) dp[i] -= MOD;
            }
        }
        ll sum = 0;
        for(int i = l; i <= r; i++) {
            sum += dp[i];
            if(sum >= MOD) sum -= MOD;
        }
        return sum * mult % MOD;
    }
};
