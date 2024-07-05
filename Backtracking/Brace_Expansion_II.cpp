#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        set<string> resultSet = backtrack(expression, 0);
        vector<string> result(resultSet.begin(), resultSet.end());
        return result;
    }

private:
    set<string> backtrack(const string &expression, int start) {
        set<string> currentSet, tempSet;
        vector<string> current;
        current.push_back("");

        while (start < expression.size()) {
            if (expression[start] == '{') {
                int end = findClosingBrace(expression, start);
                tempSet = backtrack(expression, start + 1);

                vector<string> next;
                for (const string &prefix : current) {
                    for (const string &suffix : tempSet) {
                        next.push_back(prefix + suffix);
                    }
                }
                current = move(next);
                start = end + 1;
            } else if (expression[start] == '}') {
                start++;
                break;
            } else if (expression[start] == ',') {
                currentSet.insert(current.begin(), current.end());
                current.clear();
                current.push_back("");
                start++;
            } else {
                for (string &s : current) {
                    s += expression[start];
                }
                start++;
            }
        }

        currentSet.insert(current.begin(), current.end());
        return currentSet;
    }

    int findClosingBrace(const string &expression, int start) {
        int balance = 0;
        for (int i = start; i < expression.size(); i++) {
            if (expression[i] == '{') balance++;
            if (expression[i] == '}') balance--;
            if (balance == 0) return i;
        }
        return -1;
    }
};
