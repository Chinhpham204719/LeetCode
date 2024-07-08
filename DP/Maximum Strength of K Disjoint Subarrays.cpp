#include <vector>
#include <iostream>
#include <algorithm>
#include <ios>
using namespace std;

const long long MOD = 1e9 + 7;
long long m;

vector<vector<vector<long long>>> dp;

long long solve(int i, vector<int> &nums, int k, bool flag) {
    if (k == 0)
        return 0;
    
    int n = nums.size();
    
    if (i == n) {
        if (k == 0)
            return 0;
        else 
            return -1e15;
    }
    
    if (dp[i][k][flag] != -1e16) {
        return dp[i][k][flag];
    }
    
    long long op1 = -1e15;
        
    if (flag)
        op1 = solve(i + 1, nums, k, true);
    
    long long s = (m - k) % 2 == 0 ? 1 : -1;
    long long op3 = nums[i] * 1LL * k * s + solve(i + 1, nums, k, false);
    
    long long op2 = nums[i] * 1LL * k * s + solve(i + 1, nums, k - 1, true);
  
    return dp[i][k][flag] = max({op1, op2, op3});
}

long long maximumStrength(vector<int>& nums, int k) {
    ios_base::sync_with_stdio(0);
    m = k;
    int n = nums.size();
    dp = vector<vector<vector<long long>>>(nums.size(), vector<vector<long long>>(k + 1, vector<long long>(2, -1e16)));
    return solve(0, nums, k, true);
}

int main() {
    vector<int> nums = {3, 1, -4, 5};
    int k = 2;
    cout << "Maximum Strength: " << maximumStrength(nums, k) << endl;
    return 0;
}
