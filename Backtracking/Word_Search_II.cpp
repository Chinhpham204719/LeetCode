class TrieNode {
public:
    TrieNode* children[26]; // Array to store child nodes for each character
    bool isWord; // Flag to indicate if the node represents the end of a word
    
    TrieNode() {
        // Constructor to initialize a TrieNode
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isWord = false;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Trie implementation to efficiently search words on the board.
        for (int i = 0; i < words.size(); i++) {
            insert(words[i]); // Insert all words from the dictionary into the trie.
        }
        
        int m = board.size();
        int n = board[0].size();
        
        TrieNode* node = root; // Start from the root of the trie
        vector<string> result; // Store the found words
        
        // Iterate through each cell on the board
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                search(board, i, j, m, n, node, "", result); // Start DFS search from each cell
            }
        }
        
        return result; // Return the found words
    }
private:
    TrieNode* root = new TrieNode(); // Root node of the trie
    
    // Method to insert a word into the trie
    void insert(string word) {
        TrieNode* node = root; // Start from the root
        int curr = 0;
        
        // Traverse through the trie, creating nodes as necessary
        for (int i = 0; i < word.size(); i++) {
            curr = word[i] - 'a'; // Convert character to index
            if (node->children[curr] == NULL) {
                node->children[curr] = new TrieNode(); // Create a new node if not already present
            }
            node = node->children[curr]; // Move to the next node
        }
        
        node->isWord = true; // Mark the last node as representing the end of the word
    }
    
    // Method to perform DFS search on the board
    void search(vector<vector<char>>& board, int i, int j, int m, int n, TrieNode* node, string word, vector<string>& result) {
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] == '#') {
            return; // Return if cell is out of bounds or already visited
        }
        
        char c = board[i][j]; // Get the character at the current cell
        
        node = node->children[c - 'a']; // Move to the corresponding child node in the trie
        if (node == NULL) {
            return; // Return if no matching node in the trie
        }
        
        word += board[i][j]; // Append the character to the current word
        
        if (node->isWord) {
            result.push_back(word); // Add the word to the result if it exists in the trie
            node->isWord = false; // Mark the word as found
        }
        
        board[i][j] = '#'; // Mark the cell as visited
        
        // Explore all four directions recursively
        search(board, i - 1, j, m, n, node, word, result);
        search(board, i + 1, j, m, n, node, word, result);
        search(board, i, j - 1, m, n, node, word, result);
        search(board, i, j + 1, m, n, node, word, result);
        
        board[i][j] = c; // Restore the cell value
    }
};
