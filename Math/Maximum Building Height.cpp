class Solution {
public:
    #define LL long long
    static const int mx = (int)1e5 + 10;
    LL lim[mx];
    int maxBuilding(int n, vector<vector<int>>& rest) {
        LL sz = rest.size();
        if (sz == 0) {
            return n-1;
        }
        sort(rest.begin(), rest.end());
        lim[sz] = INT_MAX;
        for (int i = sz-1; i >= 0; i--) {
            LL diff = i != 0 ? rest[i][0] - rest[i-1][0] : rest[i][0];
            LL tmp = min(lim[i+1], (LL)rest[i][1]);
            lim[i] = tmp + diff;
        }
        LL run = 0;
        LL prev = 1;
        LL ans = 0;
        for (int i = 0; i < rest.size(); i++) {
            LL dist = rest[i][0] - prev;
            LL future = min({dist + run, lim[i+1], (LL)rest[i][1]});
            LL x = run, y = future;
            if (x > y) swap(x, y);
            LL mheight = y + (dist-(y-x))/2;
            run = future;
            ans = max(ans, run);
            ans = max(ans, mheight);
            prev = rest[i][0];
        }
        ans = max(ans, n-prev+run);
        return ans;
    }
};
