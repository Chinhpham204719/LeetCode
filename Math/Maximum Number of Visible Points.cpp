class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<double> thetas;
        thetas.reserve(points.size());
        int count_offset = 0;
        for (const vector<int>& p : points) {
            if (p[0] == location[0] && p[1] == location[1]) {
                count_offset++;
            } else {
                double theta = atan2(p[1] - location[1], p[0] - location[0]);
                thetas.push_back(theta * 360.0 / (2.0*M_PI));
            }
        }

        sort(thetas.begin(), thetas.end());

        int i=0;
        int j = upper_bound(thetas.begin(), thetas.end(), thetas[i] + angle) - thetas.begin();
        int max_count = 0;
        while (true) {
            max_count = max(max_count, j - i);
            i++;
            if (i >= (int)thetas.size()) {
                break;
            }

            double thetas_j;
            while (thetas_j = (j < (int)thetas.size()) ? thetas[j] : 360.0 + thetas[j - thetas.size()],
                   thetas_j <= thetas[i] + angle) {
                j++;
            }
        }
        return max_count + count_offset;
    }
};
