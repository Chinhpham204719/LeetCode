class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();

        // DP table, init. with all zeros
        vector<vector<int>> dp(n, vector<int>(k + 1, 0));

        // Hashmap to record the last appearance of each distinct number
        // Need this for transition 1.
        unordered_map<int, int> last_seen;

        // The length of longest subseq with k unequal pairs so far
        // Need this for transition 2.
        vector<int> longest_so_far(k + 1, 0);

        // Base case: zero-th number itself is a subseq. with zero unequal pairs
        dp[0][0] = 1;
        last_seen[nums[0]] = 0;
        longest_so_far[0] = 1;
        
        // Start with the first number
        for (int i = 1; i < n; i++) {
            dp[i][0] = 1;  // The number alone is always a subseq. with 0 unequal pair
            int max_possible_p = min(i, k);

            // 1. append this number to its previous presence
            if (last_seen.find(nums[i]) != last_seen.end()) {
                for (int p = 0; p <= max_possible_p; p++) {
                    dp[i][p] = max(dp[i][p], dp[last_seen[nums[i]]][p] + 1);
                }
            }
            last_seen[nums[i]] = i;
            
            // 2. append this number to previous different number
            for (int p = 0; p <= max_possible_p; p++) {
                if (p >= k) break;
                dp[i][p + 1] = max(dp[i][p + 1], longest_so_far[p] + 1);
            }
            
            for (int p = 0; p <= max_possible_p; p++) {
                longest_so_far[p] = max(longest_so_far[p], dp[i][p]);
            }
        }
        
        int ans = 1;
        for (int p = 0; p <= k; p++) {
            ans = max(ans, longest_so_far[p]);
        }
        return ans;
    }
};
