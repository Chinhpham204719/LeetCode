#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

using ll = long long;
ll mod = 1e9 + 7;

ll numberOfStableArrays(int zero, int one, int limit) {
    vector<vector<vector<ll>>> dp(zero + 1, vector<vector<ll>>(one + 1, vector<ll>(2, 0)));
    dp[0][0][0] = 1;
    dp[0][0][1] = 1;
    unordered_map<ll, ll> z;
    unordered_map<ll, ll> o;

    z[0]++;
    o[0]++;
    
    for (ll zeros = 0; zeros <= zero; zeros++) {
        for (ll ones = 0; ones <= one; ones++) {
            if (zeros == 0 && ones == 0) continue;
            
            if (ones - limit - 1 >= 0) {
                o[zeros] = (o[zeros] % mod - dp[zeros][ones - limit - 1][0] % mod) % mod;
                o[zeros] += mod;
            }
            if (zeros - limit - 1 >= 0) {
                z[ones] = (z[ones] % mod - dp[zeros - limit - 1][ones][1] % mod) % mod;
                z[ones] += mod;
            }

            dp[zeros][ones][0] = z[ones] % mod;
            dp[zeros][ones][1] = o[zeros] % mod;

            o[zeros] = (o[zeros] % mod + dp[zeros][ones][0] % mod) % mod;
            z[ones] = (z[ones] % mod + dp[zeros][ones][1] % mod) % mod;
        }
    }

    return (dp[zero][one][1] % mod + dp[zero][one][0] % mod) % mod;
}

int main() {
    int zero = 3;
    int one = 4;
    int limit = 2;
    cout << "Number of Stable Arrays: " << numberOfStableArrays(zero, one, limit) << endl;
    return 0;
}
