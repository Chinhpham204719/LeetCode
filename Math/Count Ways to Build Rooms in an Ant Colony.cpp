class Solution {
    int mod = 1e9 + 7;
    int binExp(int a, int b) {
        int ans = 1;

        while (b > 0) {
            if (b & 0x1) {
                ans = (1LL * ans * a) % mod;
            }

            a = 1LL * a * a % mod;
            b >>= 1;
        }

        return ans;
    }

    // return the number of nodes in subtree
    int dfs(int node, vector<vector<int>>& tree, vector<int>& inv, int& ans) {
        int cnt = 1;

        for (auto c : tree[node]) {
            cnt += dfs(c, tree, inv, ans);
        }

        ans = (1LL * ans * inv[cnt]) % mod;
        return cnt;
    }
public:
    // combinatorics; math;
    int waysToBuildRooms(vector<int>& prevRoom) {
        int n = prevRoom.size();
        int fact = 1;
        
        // mod inverse of 1-n
        vector<int> inv(n + 1);
        for (int i = 1; i <= n; i++) {
            fact = 1LL * fact * i % mod;
            inv[i] = binExp(i, mod - 2);
        }

        vector<vector<int>> tree(n);
        for (int i = 0; i < n; i++) {
            if (prevRoom[i] != -1) {
                tree[prevRoom[i]].push_back(i);
            }
        }

        dfs(0, tree, inv, fact);
        return fact;
    }
};
