
class Solution {
    int nMatch(const std::string& s1, const std::string& s2) {
        int matches = 0;
        for (int i = 0; i < 6; ++i)
            if (s1[i] == s2[i])
                ++matches;
        return matches;
    }

    std::string bestCandidate (std::vector<string>& words) {
        int minMaxSubset = words.size();
        std::string best = words[0];
        for (auto& word: words)
        {
            int maxSubset = 1;
            for (auto realizedVal : {0, 1, 2, 3, 4, 5})
            {
                int subsetSize = std::count_if(words.begin(), words.end(),
                [&](auto& s) { return nMatch(s, word) == realizedVal; });
                maxSubset = std::max(maxSubset, subsetSize);
                if (maxSubset >= minMaxSubset)
                    break;
            }
            if (maxSubset < minMaxSubset)
            {
                best = word;
                minMaxSubset = maxSubset;
            }
        }
        return best;
    }

public:
    void findSecretWord(vector<string>& words, Master& master) {
        int matches = 0;

        while (matches != 6) {
            std::string guess = bestCandidate(words);
            matches = master.guess(guess);
            std::erase_if(words, [&] (auto& word) {
                    return nMatch(guess, word) != matches;
                });
        }
        return;
    }
};
