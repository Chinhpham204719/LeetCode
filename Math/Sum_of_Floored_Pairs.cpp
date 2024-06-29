class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int n=nums.size();
        vector<int>arr(200005,0);
        map<int,int>mp;
        for(auto it:nums){
            arr[it]++;
            mp[it]++;
        }
        for(int i=1;i<200005;i++)arr[i]+=arr[i-1];
        long long ans=0;
        for(auto it:mp){
            int j=1;
            long long sum=0;
            for(int i=it.first+it.first;i<200005;i+=it.first){
                sum+=(arr[i-1]-arr[i-it.first-1])*j;
                sum%=1000000007;
                j++;
            }
            ans+=(sum*it.second);
            ans%=1000000007;
        }
        return ans;
    }
};
