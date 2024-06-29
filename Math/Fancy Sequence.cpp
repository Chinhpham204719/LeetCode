#include <vector>
#include <iostream>

class Fancy {
private:
    std::vector<long long> values;
    long long totalAdd;
    long long totalMult;
    const long long MOD = 1e9 + 7;

public:
    Fancy() : totalAdd(0), totalMult(1) {}

    void append(int val) {
        long long adjustedVal = (val - totalAdd + MOD) % MOD;
        adjustedVal = (adjustedVal * modInverse(totalMult, MOD)) % MOD;
        values.push_back(adjustedVal);
    }

    void addAll(int inc) {
        totalAdd = (totalAdd + inc) % MOD;
    }

    void multAll(int m) {
        totalAdd = (totalAdd * m) % MOD;
        totalMult = (totalMult * m) % MOD;
    }

    int getIndex(int idx) {
        if (idx >= values.size()) return -1;
        long long result = (values[idx] * totalMult + totalAdd) % MOD;
        return static_cast<int>(result);
    }

private:
    long long modInverse(long long a, long long m) {
        return modPower(a, m - 2, m);
    }

    long long modPower(long long base, long long exp, long long mod) {
        long long result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base) % mod;
            }
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
};
