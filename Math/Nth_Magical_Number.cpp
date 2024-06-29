class Solution {
public:
int mod = 1e9 +7;

int check(int n,int a,int b,long long val){
    long long g = (a*b)/__gcd(a,b);
    long long cnt = 0;
    cnt += val/a;
    cnt += val/b;
    cnt -= val/g;
    if(cnt >= n) return 1;
    else return 0;
}


int nthMagicalNumber(int n, int a, int b) {
    long long low = 1L,high = ((n*1L)*min((a*1L),(b*1L))),ans = high;
    // cout<<low<<" "<<high<<"\n";
        while(low<=high){
            long long mid = (low + (high-low)/2);
            if(check(n,a,b,mid)){
                ans = mid;
                high = (mid-1);
            }
            else low = (mid+1);
        }
        // cout<<ans<<"\n";
        return ans%mod;
    }
};
