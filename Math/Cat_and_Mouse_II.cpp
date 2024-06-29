class Solution {
public:    
    bool canMouseWin(vector<string>& grid, int catJump, int mouseJump) {
        int rows = grid.size(), cols = grid[0].size();
        int catStartPos = findPos(rows, cols, grid, 'C');
        int mouseStartPos = findPos(rows, cols, grid, 'M');
        int foodPos = findPos(rows, cols, grid, 'F');
        vector<vector<int>> catTransitions = getTransitions(rows, cols, grid, catJump);
        vector<vector<int>> mouseTransitions = getTransitions(rows, cols, grid, mouseJump);

        // states[catPos][mousePos][isMouseMove]
        // = 0 for undetermined outcome, 1 for cat will win, 2 for mouse will win
        vector<vector<array<int, 2>>> states(rows * cols, vector<array<int, 2>>(rows * cols));
        // catPos, mousePos, isMouseMove
        queue<array<int, 3>> endStates;
        // number of next states that result in a loss
        vector<vector<array<int, 2>>> loseCounter(rows * cols, vector<array<int, 2>>(rows * cols));

        for (int i = 0; i < rows * cols; i++) {
            if (i == foodPos || grid[i / cols][i % cols] == '#') {
                continue;
            }
            states[foodPos][i] = {1, 1}; // cat at food
            states[i][foodPos] = {2, 2}; // mouse at food
            states[i][i] = {1, 1}; // cat caught mouse
            endStates.push({foodPos, i, false});
            endStates.push({foodPos, i, true});
            endStates.push({i, foodPos, false});
            endStates.push({i, foodPos, true});
            endStates.push({i, i, false});
            endStates.push({i, i, true});
        }
        
        // bfs from all end states
        while (endStates.size() > 0 && states[catStartPos][mouseStartPos][1] == 0) {
            auto [catPos, mousePos, isMouseMove] = endStates.front();
            endStates.pop();
            if (states[catPos][mousePos][isMouseMove] == isMouseMove + 1) {
                // end state is where cat/mouse can win on their turn
                // any previous state for mouse/cat that only leads to a win for cat/mouse must be a losing state
                if (isMouseMove) {
                    for (int previousCatPos : catTransitions[catPos]) {
                        if (states[previousCatPos][mousePos][!isMouseMove] == 0 && (++loseCounter[previousCatPos][mousePos][!isMouseMove]) == catTransitions[previousCatPos].size()) {
                            states[previousCatPos][mousePos][!isMouseMove] = 2;
                            endStates.push({previousCatPos, mousePos, !isMouseMove});
                        }
                    }
                } else {
                    for (int previousMousePos : mouseTransitions[mousePos]) {
                        if (states[catPos][previousMousePos][!isMouseMove] == 0 && (++loseCounter[catPos][previousMousePos][!isMouseMove]) == mouseTransitions[previousMousePos].size()) {
                            states[catPos][previousMousePos][!isMouseMove] = 1;
                            endStates.push({catPos, previousMousePos, !isMouseMove});
                        }
                    }
                }
            } else if (states[catPos][mousePos][isMouseMove] == 2 - isMouseMove) {
                // end state is where cat/mouse must lose on their turn
                // any previous state for mouse/cat that can lead to a loss for cat/mouse must be a winning state
                if (isMouseMove) {
                    for (int previousCatPos : catTransitions[catPos]) {
                        if (states[previousCatPos][mousePos][!isMouseMove] == 0) {
                            states[previousCatPos][mousePos][!isMouseMove] = 1;
                            endStates.push({previousCatPos, mousePos, !isMouseMove});
                        }
                    }
                } else {
                    for (int previousMousePos : mouseTransitions[mousePos]) {
                        if (states[catPos][previousMousePos][!isMouseMove] == 0) {
                            states[catPos][previousMousePos][!isMouseMove] = 2;
                            endStates.push({catPos, previousMousePos, !isMouseMove});
                        }
                    }
                }
            }
        }
        return states[catStartPos][mouseStartPos][1] == 2;
    }

private:
    int findPos(int rows, int cols, vector<string>& grid, char c) {
        for (int i = 0; i < rows * cols; i++) {
            if (grid[i / cols][i % cols] == c) {
                return i;
            }
        }
        return -1;
    }

    vector<vector<int>> getTransitions(int rows, int cols, vector<string>& grid, int jump) {
        vector<vector<int>> transitions(rows * cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == '#') {
                    continue;
                }
                transitions[i * cols + j].push_back(i * cols + j);
                for (int k = i - 1; k >= max(i - jump, 0) && grid[k][j] != '#'; k--) {
                    transitions[i * cols + j].push_back(k * cols + j);
                }
                for (int k = i + 1; k <= min(i + jump, rows - 1) && grid[k][j] != '#'; k++) {
                    transitions[i * cols + j].push_back(k * cols + j);
                }
                for (int k = j - 1; k >= max(j - jump, 0) && grid[i][k] != '#'; k--) {
                    transitions[i * cols + j].push_back(i * cols + k);
                }
                for (int k = j + 1; k <= min(j + jump, cols - 1) && grid[i][k] != '#'; k++) {
                    transitions[i * cols + j].push_back(i * cols + k);
                }
            }
        }
        return transitions;
    }
};
