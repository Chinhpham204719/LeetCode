#include <vector>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int s = 0;
    int mod = 1e9 + 7;

    int solve(int i, int prev, int mn, int k, vector<int>& nums, map<int, int> memo[][55][55]) {
        if (k == 0 && mn != INT_MAX) {
            return mn;
        }
        if (i == nums.size()) return 0;
        
        // If the result for this state is already computed, return it
        if (memo[i][k][prev+1].count(mn)) {
            return memo[i][k][prev+1][mn];
        }

        int g = solve(i + 1, prev, mn, k, nums, memo);
        int h;
        if (prev != -1) {
            h = solve(i + 1, i, min(mn, nums[i] - nums[prev]), k - 1, nums, memo);
        } else {
            h = solve(i + 1, i, mn, k - 1, nums, memo);
        }
        
        // Store the computed result in the memoization map
        return memo[i][k][prev+1][mn] = (0LL + g + h) % mod;
    }

    int sumOfPowers(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
         map<int, int> memo[nums.size()+2][55][55];
        s = solve(0, -1, INT_MAX, k, nums, memo);
        return s;
    }
};
