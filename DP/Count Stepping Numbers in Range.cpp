class Solution {
   const int M = 1000000007;
    void add(int &x, int y) {
        if ((x += y) >= M) {
            x -= M;
        }
    }
    int count(int n) {
        const int d[] = {-1, 1};
        if (n < 1) {
            return 0;
        }
        vector<vector<int>> dp(2, vector<int>(10));
        dp[0] = vector<int>(10, 1);
        dp[0][0] = 0;
        int r = 9, last = 0;
        for (int i = 2; i <= n; ++i) {
            const int now = last ^ 1;
            dp[now] = vector<int>(10);
            for (int x = 0; x < 10; ++x) {
                if (dp[last][x] == 0) {
                    continue;
                }
                for (int v : d) {
                    const int y = v + x;
                    if (y < 0 || y >= 10) {
                        continue;
                    }
                    add(dp[now][y], dp[last][x]);
                }   
            }
            for (int x : dp[now]) {
                add(r, x);
            }
            last = now;
        }
        return r;    
    }
    
    int count(const string &s, bool allowEqual = true) {
        const int d[] = {-1, 1};
        const int n = s.length();
        int r = count(n - 1);
        
        // dp[][0][d] equals
        // dp[][1][d] smaller
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(2, vector<int>(10)));
        for (int i = s[0] - '0'; i; --i) {
            dp[0][i < s[0] - '0'][i] = 1;
        }
        int last = 0;
        for (int i = 1; i < n; ++i) {
            const int now = last ^ 1;
            dp[now] = vector<vector<int>>(2, vector<int>(10));
            const int c = s[i] - '0';
            for (int j = 0; j < 2; ++j) {
                for (int x = 0; x < 10; ++x) {
                    if (dp[last][j][x] == 0) {
                        continue;
                    }
                    for (int v : d) {
                        const int y = v + x;
                        if (y < 0 || y >= 10 || (j == 0 && y > c)) {
                            continue;
                        }
                        add(dp[now][j || y < c][y], dp[last][j][x]);
                    }
                    
                }
            }
            last = now;
            
        }
        for (int i = 0; i < 10; ++i) {
            add(r, dp[last][1][i]);
            if (allowEqual) {
                add(r, dp[last][0][i]);
            }
        }
        return r;
    }
public:
    int countSteppingNumbers(string low, string high) {
       int r = count(high) - count(low, false);
        return r < 0 ? (r + M) : r;
    }
};
