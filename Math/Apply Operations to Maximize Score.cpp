
int mod = 1e9 + 7;
int dis(int x) {
    int count = 0;
    for (int i = 2; i <= sqrt(x); ++i) {
        bool flag = false;
        while (x % i == 0) {
            x /= i;
            if(!flag)
                ++count;
            flag = true;
        }
    }
    if (x > 1) {
        ++count;
    }
    return count;
}

long expo(long x, long y) {
    long res = 1;
    while(y) {
        if(y & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        y >>= 1;
    }
    return res;
}

class Solution {
public:
    int maximumScore(vector<int>& v, int k) {
        int n = v.size();
        vector<int> disPrimes;
        vector<int> idx(n);
        for(int i = 0; i < n; i += 1) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return v[i] > v[j];
        });
        
        for(int x : v) {
            disPrimes.push_back(dis(x));
        }
        
        vector<int> vl(n), vr(n);
        
        stack<int> st;
        for(int i = 0; i < n; i += 1) {
            while(!st.empty() && disPrimes[st.top()] < disPrimes[i]) {
                vr[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        while(!st.empty()) {
            vr[st.top()] = n;
            st.pop();
        }
        for(int i = n - 1; i >= 0; i -= 1) {
            while(!st.empty() && disPrimes[st.top()] <= disPrimes[i]) {
                vl[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        
        while(!st.empty()) {
            vl[st.top()] = -1;
            st.pop();
        }
        
        long ans = 1;
        for(long i = 0; i < n; i += 1) {
            int j = idx[i];
            long m = (vr[j] - vl[j] - 1LL);
            long val = (j - vl[j]) * (m - (j - vl[j] - 1LL));
            if(val <= k) {
                ans = (ans * expo(v[j], val) % mod) % mod;
                k -= val;
            } else {
                ans = (ans * expo(v[j], k) % mod) % mod;
                break;
            }
        }
        
        return ans;
    }
};
