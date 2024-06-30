class Solution {
public:
    bool kSmaller(int n, int m, int x, int k) {
        int c = 0;
        int num = x/m;
        c+=m*num;
        for(int i=num;i<n;i++){
            c+=x/(i+1);
        }
        return c >= k;
    }
    
    int findKthNumber(int m, int n, int k) {
        int lo = 0, hi = m*n, mid, res;
        
        while (lo < hi) {
            mid = lo + (hi - lo) / 2;
            
            if (kSmaller(n, m, mid, k)) hi = mid;
            else lo = mid + 1;
        }
        
        return lo;
    }
};
