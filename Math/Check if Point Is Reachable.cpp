class Solution {
public:
    bool isReachable(int a, int b) {
            while(!(a&1)||!(b&1)){
                if(!(a&1))a >>= 1;
                if(!(b&1))b >>= 1;
            }
            if(__gcd(a,b)==1)
        return true;
        return false;
    }
};
