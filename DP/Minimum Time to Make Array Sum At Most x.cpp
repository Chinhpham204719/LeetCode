class Solution {
public:
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) 
    {
        int n = nums1.size();
        vector<int> indices(n);
        int s = 0;
        int d = 0;
        for(int i=0; i<n; i++)
        {
            indices[i] = i;
            s += nums1[i];
            d += nums2[i];
        }
        if(s<=x)
        {
            return 0;
        }
        sort(indices.begin() , indices.end() , [&](const int a , const int b)
        {
            return nums2[a]<nums2[b];
        });
        vector<int> dp(n+1);
        int r = n+1;
        for(int i=1; i<=n; i++)
        {
            for(int j=i; j>0; j--)
            {
                dp[j] = max(dp[j] , dp[j-1]+nums2[indices[i-1]]*j + nums1[indices[i-1]]);
            }
        }
        for(int t=0; t<=n; t++)
        {
            if(s + d*t - dp[t] <=x)
            {
                return t;
            }
        }
    return -1;
    }
};
