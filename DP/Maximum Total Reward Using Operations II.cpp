#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// Define an ordered set using GNU PBDS library
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

class Solution {
public:
    int memo[2 * (int)(5 * 1e4) + 1]; // Dynamic programming memoization array

    // Recursive function to get the maximum reward for a given current value
    int getMaxReward(int currentValue, ordered_set &rewardsSet) {
        // Base case: if the current value is less than or equal to 0, return 0
        if (currentValue <= 0) {
            return 0;
        }

        // If the result is already computed, return it
        if (memo[currentValue] != -1) {
            return memo[currentValue];
        }

        // Get the number of elements in the set that are less than or equal to currentValue
        int count = rewardsSet.order_of_key(currentValue + 1);

        int maxReward = 0;

        // Iterate over each element up to 'count' in the ordered set
        for (int i = 0; i < count; i++) {
            int selectedReward = *rewardsSet.find_by_order(i); // Get the i-th smallest element
            int nextValue = currentValue - selectedReward;

            // Adjust nextValue if it's greater than or equal to selectedReward
            if (nextValue >= selectedReward) {
                nextValue = selectedReward - 1;
            }

            // If currentValue is in the set, update maxReward and continue
            if (rewardsSet.find(currentValue) != rewardsSet.end()) {
                maxReward = std::max(maxReward, selectedReward + 0);
                continue;
            }

            // Calculate reward with the selected value and the recursive result
            int rewardWithSelection = selectedReward + getMaxReward(nextValue, rewardsSet);
            maxReward = std::max(maxReward, rewardWithSelection);
        }

        // Store the result in the memoization array and return it
        return memo[currentValue] = maxReward;
    }

    // Solve function to initiate the process
    int solve(std::vector<int>& rewardValues) {
        int n = rewardValues.size();
        int maxInitialReward = rewardValues[n - 1]; // Get the highest reward value

        ordered_set rewardsSet;
        for (auto reward : rewardValues) {
            rewardsSet.insert(reward); // Insert all reward values into the ordered set
        }

        // Call the recursive function starting with maxInitialReward - 1
        int lowerReward = getMaxReward(maxInitialReward - 1, rewardsSet);
        return maxInitialReward + lowerReward;
    }

    // Main function to get the maximum total reward
    int maxTotalReward(std::vector<int>& rewardValues) {
        memset(memo, -1, sizeof(memo)); // Initialize memoization array with -1

        std::sort(rewardValues.begin(), rewardValues.end()); // Sort the reward values

        return solve(rewardValues); // Call the solve function and return the result
    }
};
