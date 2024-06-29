class Solution {
public:
    string abbreviateProduct(int left, int right) {
        long long suff = 1, c = 0, total = 0, max_suff = 100000000000;
        double pref = 1.0;
        
        for (int i = left; i <= right; ++i) {
            pref *= i;
            suff *= i;

            // Rút gọn phần prefix để duy trì trong khoảng 100000
            while (pref >= 100000) {
                pref /= 10;
                total = total == 0 ? 6 : total + 1; 
            }

            // Loại bỏ các số không ở cuối suffix
            while (suff % 10 == 0) {
                suff /= 10;
                ++c;
            }
            
            // Giữ suffix trong giới hạn max_suff
            suff %= max_suff;
        }
        
        // Chuyển đổi suffix thành chuỗi
        string s = to_string(suff);
        
        // Chuyển đổi prefix thành số nguyên và nối chuỗi với suffix
        string result = to_string((int)pref) + (total - c <= 10 ? "" : "...") 
                        + (total - c < 5 ? "" : s.substr(s.size() - min(5LL, total - c - 5))) 
                        + "e" + to_string(c);
        
        return result;
    }
};
