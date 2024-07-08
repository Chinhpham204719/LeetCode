#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

vector<vector<int>> adj;  // adjacency list
int n, k;
vector<int> dp;

int solve(int mask) {
    if (mask == ((1 << n) - 1)) {
        // Tất cả các khóa học đã được hoàn thành
        return 0;
    }
    if (dp[mask] != -1) {
        // Trạng thái này đã được tính trước
        return dp[mask];
    }

    vector<int> indeg(n, 0);
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) continue;
        for (auto it : adj[i]) {
            indeg[it]++;
        }
    }

    int temp = 0;  // Mask cho tất cả các khóa học có bậc vào bằng 0
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0 && !(mask & (1 << i))) {
            temp |= (1 << i);
        }
    }

    int j = temp;
    int cnt = __builtin_popcount(j);  // Đếm số khóa học với bậc vào bằng 0
    int ans = n + 1;  // Giá trị lớn hơn số học kỳ tối đa

    if (cnt > k) {
        for (; j; j = (j - 1) & temp) {  // Duyệt qua tất cả các tập con của `temp`
            cnt = __builtin_popcount(j);
            if (cnt != k) continue;
            ans = min(ans, 1 + solve(mask | j));
        }
    } else {
        ans = min(ans, 1 + solve(mask | j));
    }
    
    return dp[mask] = ans;
}

int minNumberOfSemesters(int N, vector<vector<int>>& d, int K) {
    n = N;
    k = K;
    dp.assign(1 << n, -1);
    adj.clear();
    adj.resize(n);
    
    for (int i = 0; i < d.size(); i++) {
        d[i][0]--;
        d[i][1]--;
        adj[d[i][0]].push_back(d[i][1]);
    }
    
    return solve(0);
}

int main() {
    vector<vector<int>> dependencies = {{1, 2}, {2, 3}, {3, 4}};
    int N = 4;
    int K = 2;
    cout << minNumberOfSemesters(N, dependencies, K) << endl;
    return 0;
}
