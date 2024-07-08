#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

// Hàm tìm độ dài lớn nhất của dãy con với không quá k cặp phần tử khác nhau
int maximumLength(vector<int>& nums, int k) {
    int n = nums.size();

    // Bảng DP, khởi tạo tất cả các giá trị là 0
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    // Hashmap để ghi lại lần xuất hiện cuối cùng của mỗi số khác nhau
    unordered_map<int, int> last_seen;

    // Độ dài của dãy con dài nhất với k cặp phần tử khác nhau tính đến hiện tại
    vector<int> longest_so_far(k + 1, 0);

    // Trường hợp cơ bản: số đầu tiên là một dãy con với 0 cặp phần tử không bằng nhau
    dp[0][0] = 1;
    last_seen[nums[0]] = 0;
    longest_so_far[0] = 1;

    // Bắt đầu từ số thứ nhất
    for (int i = 1; i < n; i++) {
        dp[i][0] = 1;  // Một số duy nhất luôn là một dãy con với 0 cặp phần tử không bằng nhau
        int max_possible_p = min(i, k);

        // 1. Nối số này vào lần xuất hiện trước đó
        if (last_seen.find(nums[i]) != last_seen.end()) {
            for (int p = 0; p <= max_possible_p; p++) {
                dp[i][p] = max(dp[i][p], dp[last_seen[nums[i]]][p] + 1);
            }
        }
        last_seen[nums[i]] = i;

        // 2. Nối số này vào các dãy con trước đó có phần tử kết thúc khác
        for (int p = 0; p <= max_possible_p; p++) {
            if (p >= k) break;
            dp[i][p + 1] = max(dp[i][p + 1], longest_so_far[p] + 1);
        }

        for (int p = 0; p <= max_possible_p; p++) {
            longest_so_far[p] = max(longest_so_far[p], dp[i][p]);
        }
    }

    int ans = 1;
    for (int p = 0; p <= k; p++) {
        ans = max(ans, longest_so_far[p]);
    }
    return ans;
}

// Hàm kiểm tra
int main() {
    vector<int> nums = {1, 2, 2, 3, 3, 4, 5};
    int k = 2;
    int result = maximumLength(nums, k);
    cout << "Độ dài lớn nhất của dãy con: " << result << endl;
    return 0;
}
