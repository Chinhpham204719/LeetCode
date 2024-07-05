class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        constexpr int invalid = -1;
        const int n_stickers = static_cast<int>(stickers.size());
        const int n_target = static_cast<int>(target.size());
        const int n_layouts = (1 << n_target);
        long letter_to_stickers[26] = {};
        int dp[32768];
        
        for (int i_sticker = 0; i_sticker < n_stickers; ++i_sticker)
            for (const char c : stickers[i_sticker])
                letter_to_stickers[c - 'a'] |= (1L << i_sticker);
        std::memset(dp, invalid, sizeof(dp));
        dp[0] = 0;
        for (int layout = 0; layout < n_layouts; ++layout)
        {
            if (dp[layout] == invalid)
                continue;
            int letter = -1;
            for (int i_target = 0; i_target < n_target; ++i_target)
            {
                if (!((layout >> i_target) & 1)
                &&  (letter_to_stickers[target[i_target] - 'a'] != 0))
                {
                    letter = target[i_target] - 'a';
                    break;
                }
            }
            if (letter == -1) break;
            for(int i_sticker = 0; i_sticker < n_stickers; ++i_sticker)
            {
                if (((letter_to_stickers[letter] >> i_sticker) & 1) == 0)
                    continue;
                int next_layout = layout;
                for (const char c_sticker : stickers[i_sticker])
                {
                    for (int i_target = 0; i_target < n_target; ++i_target)
                    {
                        if ((target[i_target] == c_sticker)
                        &&  (((next_layout >> i_target) & 1) == 0))
                        {
                            next_layout |= (1 << i_target);
                            break;
                        }
                    }
                }
                dp[next_layout] = (dp[next_layout] == invalid)
                                    ?(dp[layout] + 1)
                                    :std::min(dp[next_layout], dp[layout] + 1);
            }
        }
        return dp[n_layouts - 1];
    }
};
