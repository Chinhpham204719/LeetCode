class Solution {
public:
    int numPoints(vector<vector<int>>& darts, int r) {
        int maximum = 1;
        //finding all three-unique points combinations
        for(int i = 0; i<darts.size(); i++){
            for(int j = i+1; j<darts.size(); j++){
                for(int k = j+1; k<darts.size(); k++){
                    double x1 = darts[i][0];
                    double y1 = darts[i][1];
                    double x2 = darts[j][0];
                    double y2 = darts[j][1];
                    double x3 = darts[k][0];
                    double y3 = darts[k][1];
                    double ox, oy;
                    
                    //obtaining the circumcenter from the formula mentioned before
                    double denominator = 2 * ((x1 * (y2 - y3)) + (x2 * (y3 - y1)) + (x3 * (y1 - y2)));
                    ox = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / denominator;
                    oy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / denominator;

                    //counter for the number of circles contained by this circle
                    int runningCount = 0;
                    for(int t = 0; t<darts.size(); t++){
                        //using distance formula
                        if((double)sqrt((double)pow(ox-darts[t][0],2)+(double)pow(oy-darts[t][1],2))<=(double)r)runningCount++;
                    }
                    //maximising the final result
                    maximum  = max(maximum,runningCount);
                }
            }
        }
        return maximum;
    }
};
