class Solution {
public:
    int k2;
    bool check(long long mid)
    {
        int count=0;
        while(mid>0)
        {
            count+=mid/5;
            mid/=5;
        }
        return count<=k2;
    }
    int preimageSizeFZF(int k) {
        long long l=0;
        long long r=5*1e9;
        long long ans=0;
        k2=k;
        while(l<=r)
        {
            long long mid=(l+r)/2;
            if(check(mid))
            {
                l=mid+1;
                ans=mid;
            }
            else
                r=mid-1;
        }
        int count=0;
        while(ans>0)
        {
            count+=ans/5;
            ans/=5;
        }
        return 5*(count==k);
    }
};
