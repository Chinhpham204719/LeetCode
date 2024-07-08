#include <vector>
#include <climits>
#include <cmath>
#include <iostream>
using namespace std;

// Các biến toàn cục
vector<int> perm;
int min_score = INT_MAX;

// Hàm đệ quy chính để tìm hoán vị với tổng điểm nhỏ nhất
void helper(int n, int mask, vector<int>& nums, vector<int>& vec, int score) {
    if (score >= min_score)  // Tránh các tính toán vô ích nếu điểm số hiện tại đã cao hơn điểm số nhỏ nhất
        return;
    if (vec.size() == n) {
        // Tính tổng điểm khi hoàn thành hoán vị
        score += abs(nums[vec[0]] - nums[vec[vec.size() - 1]]);
        if (score < min_score) {
            min_score = score;
            perm = vec;
        }
        return;
    }
    for (int i = 1; i < n; i++) {
        if (!(mask & (1 << i))) { // Kiểm tra xem phần tử đã được sử dụng hay chưa
            vec.push_back(i);
            helper(n, mask | (1 << i), nums, vec, score + abs(nums[vec[vec.size() - 1]] - nums[vec[vec.size() - 2]]));
            vec.pop_back();
        }
    }
}

// Hàm chính để tìm hoán vị
vector<int> findPermutation(vector<int>& nums) {
    int n = nums.size();
    vector<int> vec;
    vec.push_back(0); // Bắt đầu từ phần tử đầu tiên
    helper(n, 1, nums, vec, 0); // Bắt đầu với bitmask 1 (chỉ số 0 đã được sử dụng)
    return perm;
}

// Hàm chính để kiểm tra
int main() {
    vector<int> nums = {4, 2, 7, 1};
    vector<int> result = findPermutation(nums);
    cout << "Hoán vị với tổng điểm nhỏ nhất: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
