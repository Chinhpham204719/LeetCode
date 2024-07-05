class Solution {
public:
   
    bool helper(vector<int>& counts, vector<int>& quantity, int index) {
        // Base case: All quantities have been distributed successfully
        if (index == quantity.size()) {
            return true;
        }

        // Try distributing the current quantity at the current index
        for (int i = 0; i < counts.size(); ++i) {
            if (counts[i] >= quantity[index]) {
                counts[i] -= quantity[index];

                // Recursively check the next quantity
                if (helper(counts, quantity, index + 1)) {
                    return true;
                }

                // Backtrack by restoring the counts
                counts[i] += quantity[index];
            }
        }
        return false;
    }

   
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        unordered_map<int, int> countMap;

        // Count occurrences of each unique element in nums
        for (auto num : nums) {
            countMap[num]++;
        }

        // Extract counts and sort quantities in descending order
        vector<int> counts;
        for (auto i : countMap) {
            counts.push_back(i.second);
        }
        sort(quantity.rbegin(), quantity.rend());

        // Check if distribution is possible using the helper function
        return helper(counts, quantity, 0);
    }
};
