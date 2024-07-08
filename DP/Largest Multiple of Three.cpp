string largestMultipleOfThree(vector<int>& digits) {
    sort(digits.rbegin(),digits.rend()); // Sắp xếp mảng theo thứ tự giảm dần
    int n = digits.size();
    int sum = accumulate(digits.begin(),digits.end(),0); // Tính tổng các số trong mảng

    if(sum == 0) return "0"; // Nếu tổng bằng 0, trả về "0"
    if(sum % 3 == 0) return make_string(digits); // Nếu tổng chia hết cho 3, trả về chuỗi số đã sắp xếp

    int one = 0, two = 0;
    map<int,vector<int>> m;

    // Phân loại các số theo dư của phép chia cho 3
    for(auto it : digits) {
        if((it % 3) == 1) {
            m[1].push_back(it);
            one++;
        } else if((it % 3) == 2) {
            m[2].push_back(it);
            two++;
        } else {
            m[0].push_back(it);
        }
    }

    // Xử lý các trường hợp cần loại bỏ số
    if(sum % 3 == 1) {
        if(!m[1].empty()) {
            m[1].pop_back();
        } else {
            m[2].pop_back();
            m[2].pop_back();
        }
    } else {
        if(!m[2].empty()) {
            m[2].pop_back();
        } else {
            m[1].pop_back();
            m[1].pop_back();
        }
    }

    // Xây dựng chuỗi kết quả từ các số trong map m
    string ans = "";
    for(int i = 0; i < 3; i++) {
        for(auto it : m[i]) {
            ans += (it + '0');
        }
    }

    sort(ans.rbegin(), ans.rend()); // Sắp xếp chuỗi kết quả theo thứ tự giảm dần
    if(ans[0] == '0') return "0"; // Nếu chuỗi kết quả bắt đầu bằng '0', trả về "0"
    return ans;
}
