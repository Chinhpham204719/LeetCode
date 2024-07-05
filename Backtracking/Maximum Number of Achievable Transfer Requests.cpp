class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int answer = 0;
        vector<int> indegree(n, 0);

        function<void(int, int)> maxRequest = [&](int index, int count) {
            if (index == requests.size()) {
                for (int i = 0; i < n; i++) {
                    if (indegree[i]) {
                        return;
                    }
                }
                answer = max(answer, count);
                return;
            }

            indegree[requests[index][0]]--;
            indegree[requests[index][1]]++;

            maxRequest(index + 1, count + 1);

            indegree[requests[index][0]]++;
            indegree[requests[index][1]]--;

            maxRequest(index + 1, count);
        };

        maxRequest(0, 0);

        return answer;
    }
};
