#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    unordered_map<int, vector<pair<int, int>>> graph;
    int result = 0;

    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }
        vector<int> visited(values.size(), 0);
        backtrack(values, visited, 0, 0, 0, maxTime);
        return result;
    }

private:
    void backtrack(vector<int>& values, vector<int>& visited, int idx, int time, int value, int maxTime) {
        if (time > maxTime) {
            return;
        }
        if (visited[idx] == 0) {
            value += values[idx];
        }
        if (idx == 0) {
            result = max(result, value);
        }
        visited[idx]++;
        for (const auto& neighbor : graph[idx]) {
            backtrack(values, visited, neighbor.first, time + neighbor.second, value, maxTime);
        }
        visited[idx]--;
    }
};
