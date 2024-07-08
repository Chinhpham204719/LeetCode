#include <vector>
#include <string>

using namespace std;

string findTheString(vector<vector<int>>& lcp) {
    int n = lcp.size();
    string ans = "";

    // Kiểm tra điều kiện ban đầu
    if (lcp[0][0] != n) {
        return ans;
    }

    // Kiểm tra điều kiện LCP và thứ tự kí tự
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lcp[i][j] != lcp[j][i] || lcp[i][j] > n - max(i, j)) {
                return ans;
            }
            if (i + 1 < n && j + 1 < n && lcp[i][j] > 0 && lcp[i + 1][j + 1] != lcp[i][j] - 1) {
                return ans;
            }
        }
    }

    // Khởi tạo chuỗi kết quả ban đầu
    for (int i = 0; i < n; ++i) {
        ans += '1';
    }

    // Duyệt qua từng vị trí trong ma trận LCP để gán các kí tự
    int t = 0;
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = i; j < n; ++j) {
            if (ans[j] == '1' && lcp[i][j] != 0) {
                if (t >= 26) {
                    return "";
                }
                ans[j] = 'a' + t;
                flag = true;
            }
        }
        if (flag) {
            t++;
        }
    }

    // Kiểm tra lại các điều kiện cuối cùng của chuỗi kết quả
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (lcp[i][j] != 0 && ans[i] != ans[j]) {
                return "";
            }
        }
    }

    return ans;
}
