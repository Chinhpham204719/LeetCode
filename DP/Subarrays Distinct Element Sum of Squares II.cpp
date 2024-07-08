int MOD = 1e9 + 7;

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        // jank
        // If all elements are distinct, return sum of sum of squares
        unordered_set<int> s;
        for (int & a : nums) {
            s.insert(a);
        }
        if (s.size() == n) {
            long long ans = 0;
            for (int i = 1; i <= n; i++) {
                ans += (long long)i * (i + 1) * (2 * i + 1) / 6;
                ans %= MOD;
            }
            return ans;
        }
        // O(n * number of distinct elements)
        vector<int> v;
        unordered_map<int, int> m;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int a = nums[i];
            v.push_back(1);
            // if element existed before, find previous occurrance and merge the 2 adjacent runs together
            if (m.count(a)) {
                int suffix = 0;
                for (int j = v.size() - 2; j >= 0; j--) {
                    suffix += v[j];
                    if (suffix >= i - m[a]) {
                        v[j] += v[j + 1];
                        v.erase(v.begin() + j + 1);
                        break;
                    }
                }
            }
            m[a] = i;
            // update ans
            for (int j = 0; j < v.size(); j++) {
                ans += ((((v.size() - j) * (v.size() - j)) % MOD) * v[j]) % MOD;
                ans %= MOD;
            }
        }
        return ans;
    }
};
