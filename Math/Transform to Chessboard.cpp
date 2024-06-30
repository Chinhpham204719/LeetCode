class Solution {
public:
         int movesToChessboard(vector<vector<int>>& board) {
        int n = board.size();
        int row_counter = 0, col_counter = 0;
        for(int r = 0; r < n; r++){
            row_counter += board[r][0] ? 1 : -1;
            for(int c = 0; c < n; c++){
                if(r == 0) col_counter += board[r][c] ? 1 : -1;
                if((board[r][0] ^ board[0][0]) ^ (board[r][c] ^ board[0][c])) return -1; 
            }
        }
        if(abs(row_counter) > 1 || abs(col_counter) > 1) return -1;
        int row_swap_count = 0, col_swap_count = 0, row_0_count = 0, col_0_count = 0;
        for(int i = 0; i < n; i++){
            if(i & 1){
                row_swap_count += board[i][0];
                col_swap_count += board[0][i];
            }
            row_0_count += board[i][0] == 0, col_0_count += board[0][i] == 0;            
        }
        int odd_position_count = n/2; 
        if(n & 1){ 
            row_swap_count = row_0_count == odd_position_count ? row_swap_count : (odd_position_count - row_swap_count);
            col_swap_count = col_0_count == odd_position_count ? col_swap_count : (odd_position_count - col_swap_count);
        }
        else{
            row_swap_count = min(row_swap_count, odd_position_count - row_swap_count);
            col_swap_count = min(col_swap_count, odd_position_count - col_swap_count);            
        }
        return row_swap_count + col_swap_count;
    } 
};
