class Solution {
 public:
  int maxValueAfterReverse(vector<int>& nums) {
    int total = 0;
    int x = INT_MAX;
    int y = INT_MIN;

    for (int i = 0; i  < nums.size()-1; ++i) {
      int a = nums[i];
      int b = nums[i + 1];
      total += abs(a - b);
      x = min(x, std::max(a, b));
      y = max(y, std::min(a, b));
    }
    int diff = max(0, (y-x) * 2);

    for (int i = 0; i  < nums.size()-1; ++i) {
      int a = nums[i];
      int b = nums[i + 1];
      int headDiff = -abs(a - b) + abs(nums.front() - b);
      int tailDiff = -abs(a - b) + abs(nums.back() - a);
      diff = max({diff, headDiff, tailDiff});
    }

    return total + diff;
  }
};
