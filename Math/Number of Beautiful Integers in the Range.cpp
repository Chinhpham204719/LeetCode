class Solution {
public:
    int dp[11][2][11][100][11][2];
    int solve(int idx, int edge, int even, int rem, int odd, int zero, string s, int k){
        if(idx == s.length()) {
            if(even == odd && rem == 0 && !zero) return 1;
            return 0;
        }
        if(dp[idx][edge][even][rem][odd][zero] != -1) return dp[idx][edge][even][rem][odd][zero];
        int ans = 0;
        int max_digit = 9;
        if(edge) max_digit = s[idx] - '0';
        for(int i =  0; i<= max_digit; i++){
            // case which i forgot to take is the case of trailing zero. 
            int new_edge = (s[idx] - '0' == i)? edge:0;
            int new_rem = (rem*10 + i) % k;
            int new_odd = odd;
            int new_even = even;
            int new_zero = zero;
            if(!zero || i > 0){
                if(i%2 == 0) new_even += 1;
            }
            if(i%2 == 1) new_odd += 1;
            if(i!= 0 && new_zero) new_zero = 0;
            ans += solve(idx + 1, new_edge, new_even, new_rem, new_odd, new_zero, s, k);
        }
        return dp[idx][edge][even][rem][odd][zero] = ans;
    }
    int numberOfBeautifulIntegers(int low, int high, int k) {
        string s1 = to_string(low - 1);
        string s2 = to_string(high);
        memset(dp, -1, sizeof(dp));
        int ans1 = solve(0, 1, 0, 0, 0, 1, s1, k);
        memset(dp, -1, sizeof(dp)); 
        int ans2 = solve(0, 1, 0, 0, 0, 1, s2, k);
        return ans2 - ans1;
    }
};
