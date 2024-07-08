#include <iostream>
#include <vector>
#include <string>
using namespace std;

int numDecodings(string s) {
    long long MOD = 1e9 + 7;
    int n = s.length();
    vector<long long> dp(n + 1);
    if (s[0] == '0') return 0;
    dp[0] = 1;
    dp[1] = (s[0] == '*') ? 9 : 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = 0;
        if (s[i - 1] == '*') {
            dp[i] = (9 * dp[i - 1]) % MOD;
            if (s[i - 2] == '1') {
                dp[i] = (dp[i] + (9 * dp[i - 2]) % MOD) % MOD;
            }
            if (s[i - 2] == '2') {
                dp[i] = (dp[i] + (6 * dp[i - 2]) % MOD) % MOD;
            }
            if (s[i - 2] == '*') {
                dp[i] = (dp[i] + (15 * dp[i - 2]) % MOD) % MOD;
            }
        } else if (s[i - 1] == '0') {
            if (s[i - 2] == '1' || s[i - 2] == '2') {
                dp[i] = dp[i - 2];
            } else if (s[i - 2] == '*') {
                dp[i] = (2 * dp[i - 2]) % MOD;
            }
        } else {
            dp[i] = dp[i - 1];
            if (s[i - 2] == '*') {
                if (s[i - 1] <= '6') {
                    dp[i] = (dp[i] + (2 * dp[i - 2]) % MOD) % MOD;
                } else {
                    dp[i] = (dp[i] + dp[i - 2]) % MOD;
                }
            } else {
                int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
                if (num >= 10 && num <= 26) {
                    dp[i] = (dp[i] + dp[i - 2]) % MOD;
                }
            }
        }
    }
    return dp[n];
}

int main() {
    string s = "1*";
    cout << numDecodings(s) << endl;
    return 0;
}
