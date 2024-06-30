class Solution {
public:
    // Declare the dp array to store the results of subproblems
    vector<vector<int>> dp;

    // Function to calculate the maximum score for the segment from st to end
    int f(vector<int>& pref_sum, int st, int end) {
        // Base case: if the start index is greater than or equal to the end index, return 0
        if (st >= end) return 0;
        
        // If the result for this subproblem is already calculated, return it
        if (dp[st][end] != -1) return dp[st][end];
        
        // Initialize the score to 0
        int score = 0;
        
        // Iterate through all possible split points
        for (int i = st; i <= end; i++) {
            // Calculate the left segment sum
            int lf = (st == 0) ? pref_sum[i] : pref_sum[i] - pref_sum[st-1];
            // Calculate the right segment sum
            int rt = pref_sum[end] - pref_sum[i];
            
            // If the left segment sum is greater than the right, maximize score using the right segment
            if (lf > rt) 
                score = max(score, rt + f(pref_sum, i + 1, end));
            // If the right segment sum is greater than the left, maximize score using the left segment
            else if (lf < rt) 
                score = max(score, lf + f(pref_sum, st, i));
            // If both segments are equal, maximize score using both possible segments
            else 
                score = max({score, rt + f(pref_sum, i + 1, end), lf + f(pref_sum, st, i)});
        }
        // Store the result in the dp array and return it
        return dp[st][end] = score;
    }
    
    // Main function to calculate the maximum score for the entire array
    int stoneGameV(vector<int>& v) {
        int n = v.size();  // Get the size of the array
        dp.clear();  // Clear the dp array
        dp.resize(n + 1, vector<int>(n + 1, -1));  // Resize the dp array and initialize it with -1
        
        // Create the prefix sum array
        vector<int> pref_sum(n + 1, 0);
        pref_sum[0] = v[0];
        for (int i = 1; i < n; i++) 
            pref_sum[i] = v[i] + pref_sum[i-1];
        
        // Call the recursive function and return the result
        return f(pref_sum, 0, n - 1);
    }
};
