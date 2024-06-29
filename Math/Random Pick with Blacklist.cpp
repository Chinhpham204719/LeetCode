static const auto init = []{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    return false;
}();
int prefsum[100005];
int psz = 0;

class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        ::sort(begin(blacklist), end(blacklist));
        psz = 0;
        int pre = 0;
        int sz = blacklist.size();
        for (int i = 0; i < sz;) {
            int j = i+1;
            while (j < sz && blacklist[j] == blacklist[j-1] + 1) {++j;}
            if (blacklist[i] != 0) {
                intv.push_back({pre, blacklist[i]-1});
            }
            pre = blacklist[j-1] + 1;
            i = j;
        }
        if (pre <= n-1) {
            intv.push_back({pre, n-1});
        }
        total = 0;
        for (int i = 0; i < intv.size(); ++i) {
            int length = intv[i].second - intv[i].first + 1;
            prefsum[psz++] = total;
            total += length;
        }
    }
    int pick() {
        int r = rand()%total;
        int idx = upper_bound(prefsum, prefsum+psz, r) - prefsum - 1;
        int offset = r - prefsum[idx];
        return intv[idx].first + offset;
    }
    vector<pair<int,int>> intv;
    int total;
};
