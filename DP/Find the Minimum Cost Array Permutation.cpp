class Solution {
public:
    vector<int> perm;
    int min_score = INT_MAX;
    void helper(int n, int mask, vector<int>& nums, vector<int>& vec, int score){
        if(score >= min_score)  // This will avoid TLE
            return ;
        if(vec.size() == n){
            score += abs(nums[vec[0]] - vec[vec.size() - 1]);
            if(score < min_score){
                min_score = score;
                perm = vec;
            }
            return ;
        }
        for(int i = 1 ; i < n ; i++){
            if(!(mask & (1 << i))){
                vec.push_back(i);
                helper(n, mask | (1 << i), nums, vec, score + abs(nums[vec[vec.size() - 1]] - vec[vec.size() - 2]));
                vec.pop_back();
            }
        }
    }
    
    vector<int> findPermutation(vector<int>& nums) {
        int n = nums.size();
        vector<int> vec;
        vec.push_back(0);
        helper(n, 1, nums, vec, 0);
        return perm;
    }
};
