class Solution {
    const int M = 1000000007;
    int mul(long long x, long long y) {
        return x * y % M;
    }
    
    int add(int x, int y) {
        if ((x += y) >= M) {
            x -= M;
        }
        return x; 
    }

public:
    int sumOfPower(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        const int n = nums.size();
        int r = mul(mul(nums[0], nums[0]), nums[0]);
        for (int i = 1, last = 0; i < n; ++i) {
            last = add(nums[i - 1], add(last, last));
            r = add(r, mul(add(last, nums[i]), mul(nums[i], nums[i])));
        }
        
        return r;
    }
};
