#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxOddEvenSubarraySum(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;

    vector<int> dp(n, 0);
    dp[0] = nums[0];
    int result = dp[0];

    for (int i = 1; i < n; ++i) {
        if ((nums[i] % 2 == 0 && nums[i - 1] % 2 != 0) || (nums[i] % 2 != 0 && nums[i - 1] % 2 == 0)) {
            dp[i] = dp[i - 1] + nums[i];
        } else {
            dp[i] = nums[i];
        }
        result = max(result, dp[i]);
    }

    return result;
}

int main() {
    vector<int> nums = {0, 1, 0, 2, 3};
    cout << "Tong lon nhat cua day con chan le la: " << maxOddEvenSubarraySum(nums) << endl;
    return 0;
}
