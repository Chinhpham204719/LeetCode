#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

long long pos(const vector<int>& nums, const vector<int>& andValues, int ind, int value, int covered, unordered_map<int, unordered_map<int, unordered_map<int, int>>>& dp) {
    if (covered >= andValues.size()) return 1e6;
    if (ind >= nums.size()) {
        if (value == andValues.back() && covered + 1 == andValues.size()) return nums[ind - 1];
        return 1e6;
    }
    if (dp.find(ind) != dp.end() && dp[ind].find(covered) != dp[ind].end() && dp[ind][covered].find(value) != dp[ind][covered].end())
        return dp[ind][covered][value];

    long long select = 1e6, unselect = 1e6;
    if (value == andValues[covered]) {
        unselect = pos(nums, andValues, ind + 1, value & nums[ind], covered, dp);
        select = nums[ind - 1] + pos(nums, andValues, ind + 1, nums[ind], covered + 1, dp);
        return dp[ind][covered][value] = min(unselect, select);
    }
    unselect = pos(nums, andValues, ind + 1, value & nums[ind], covered, dp);
    return dp[ind][covered][value] = min(select, unselect);
}

int minimumValueSum(const vector<int>& nums, const vector<int>& andValues) {
    unordered_map<int, unordered_map<int, unordered_map<int, int>>> dp;
    long long res = pos(nums, andValues, 1, nums[0], 0, dp);
    return (res >= 1e6) ? -1 : res;
}

int main() {
    vector<int> nums = {4, 8, 6, 2, 10};
    vector<int> andValues = {4, 0};
    cout << "Minimum Value Sum: " << minimumValueSum(nums, andValues) << endl;
    return 0;
}
