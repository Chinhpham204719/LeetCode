class Solution {
private:
    int countMax(string& s, vector<vector<int>>& stats){
        int n = s.size();
        int cnt = 0;
        for(int i=0; i<n; i++){
            if(s[i] == '0') continue;
            cnt++;
            for(int j=0; j<n; j++){
                if(stats[i][j] == 1 && s[j] == '0') return 0;
                if(stats[i][j] == 0 && s[j] == '1') return 0;
            }
        }
        return cnt;
    }
private:
    int solver(int i, string s, vector<vector<int>>& stats){
        if(i == stats.size()){
            return countMax(s,stats);
        }

        int good = solver(i+1,s+'1',stats);
        int bad = solver(i+1,s+'0',stats);

        return max(good,bad);
    }
public:
    int maximumGood(vector<vector<int>>& statements) {
        
        return solver(0,"",statements);
    }
};
