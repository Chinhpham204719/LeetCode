#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

long long maxBalancedSubsequenceSum(vector<int>& nums) {
    int n = nums.size();
    vector<int> val(n);
    
    // Tạo mảng val từ nums[i] - i
    for (int i = 0; i < n; ++i) {
        val[i] = nums[i] - i;
    }
    
    map<int, long long> mp;
    set<int> st;
    st.insert(val[0]);
    mp[val[0]] = nums[0];
    long long ans = nums[0];
    
    for (int i = 1; i < n; ++i) {
        auto it = st.upper_bound(val[i]);
        
        if (it == st.begin()) {
            mp[val[i]] = nums[i];
        } else {
            --it;
            mp[val[i]] = max(nums[i] + mp[*it], 1LL * nums[i]);
        }
        
        ++it;
        while (it != st.end() && mp[*it] <= mp[val[i]] && *it > val[i]) {
            st.erase(it++);
        }
        
        st.insert(val[i]);
        ans = max(ans, mp[val[i]]);
    }
    
    return ans;
}

int main() {
    vector<int> nums = {3, 1, 5, 8, 2, 6, 4, 7};
    long long result = maxBalancedSubsequenceSum(nums);
    cout << "Maximum balanced subsequence sum: " << result << endl;
    
    return 0;
}
