class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return {};
        
        unordered_map<string, vector<string>> graph;
        unordered_map<string, int> distance;
        
        bfs(beginWord, endWord, wordSet, graph, distance);
        
        vector<vector<string>> result;
        vector<string> path = {beginWord};
        backtrack(beginWord, endWord, graph, distance, path, result);
        
        return result;
    }

private:
    void bfs(const string& beginWord, const string& endWord, unordered_set<string>& wordSet,
             unordered_map<string, vector<string>>& graph, unordered_map<string, int>& distance) {
        queue<string> q;
        q.push(beginWord);
        distance[beginWord] = 0;
        
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            vector<string> neighbors = getNeighbors(current, wordSet);
            
            for (const string& neighbor : neighbors) {
                graph[current].push_back(neighbor);
                if (distance.find(neighbor) == distance.end()) {
                    distance[neighbor] = distance[current] + 1;
                    q.push(neighbor);
                }
            }
        }
    }
    
    vector<string> getNeighbors(const string& word, const unordered_set<string>& wordSet) {
        vector<string> neighbors;
        for (int i = 0; i < word.size(); ++i) {
            string temp = word;
            for (char c = 'a'; c <= 'z'; ++c) {
                temp[i] = c;
                if (wordSet.find(temp) != wordSet.end() && temp != word) {
                    neighbors.push_back(temp);
                }
            }
        }
        return neighbors;
    }
    
    void backtrack(const string& current, const string& endWord,
                   unordered_map<string, vector<string>>& graph, unordered_map<string, int>& distance,
                   vector<string>& path, vector<vector<string>>& result) {
        if (current == endWord) {
            result.push_back(path);
            return;
        }
        
        for (const string& neighbor : graph[current]) {
            if (distance[neighbor] == distance[current] + 1) {
                path.push_back(neighbor);
                backtrack(neighbor, endWord, graph, distance, path, result);
                path.pop_back();
            }
        }
    }
};

// Helper function to print the vector of vectors of strings
void printResult(const vector<vector<string>>& sequences) {
    for (const auto& sequence : sequences) {
        for (const string& word : sequence) {
            cout << word << " ";
        }
        cout << endl;
    }
}
