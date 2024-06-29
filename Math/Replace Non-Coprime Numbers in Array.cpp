class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> ans;
        for(auto i: nums){
            while(!ans.empty() && __gcd(ans.back(),i) != 1){
                i = (i*1LL*ans.back())/__gcd(i,ans.back());
                ans.pop_back();
            }
            ans.push_back(i);
        }
        return ans;
    }
};
