class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(nullptr);
        std::cin.tie(nullptr);
        unordered_map<int,int> mpp;
        long long ans=0;
        for(auto i:nums){
            int get=__gcd(k,i);
            int need=k/get;
            for(auto j:mpp){
                if(j.first%need==0){
                    ans+=j.second;
                }
            }
            mpp[get]++;
        }
        return ans;
    }
};
