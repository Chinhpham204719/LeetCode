class Solution
{
public:
    int maxIncreasingCells(vector<vector<int>> &mat)
    {
        // Comparator to store values in decreasing order.
        auto comp = [](int a, int b)
        { return a > b; };
        set<int, decltype(comp)> s(comp);

        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        vector<int> rowMax(n, 0), colMax(m, 0);

        // This will help if same value exists at multiple indices.
        unordered_map<int, vector<pair<int, int>>> mapp; 

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s.insert(mat[i][j]); // Store unique values in the set.
                mapp[mat[i][j]].push_back({i, j}); // Store their indices too.
            }
        }

        // Start from Max Element and go till Min Element.
        for (auto unique : s)
        {
            for (auto index : mapp[unique])
            {
                auto [i, j] = index;
                dp[i][j] = max(rowMax[i], colMax[j]) + 1;
            }

            // Update the maximum after processing all the indices
            for (auto index : mapp[unique])
            {
                auto [i, j] = index;
                rowMax[i] = max(rowMax[i], dp[i][j]);
                colMax[j] = max(colMax[j], dp[i][j]);
            }
        }
        int colMaxi = *max_element(colMax.begin(), colMax.end());
        int rowMaxi = *max_element(rowMax.begin(), rowMax.end());
        return max(colMaxi, rowMaxi);
    }
};
