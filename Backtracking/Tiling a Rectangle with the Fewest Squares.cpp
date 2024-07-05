class Solution {
    bool isAvailable( vector<vector<bool>>& dp, int r, int c, int k ) {
        int R = r+k, C = c+k;
        for( int r1=r; r1<R; r1++ )
            for( int c1 = c; c1<C; c1++ ) 
                if( dp[r1][c1] == true )
                    return false;
        return true;
    }

    void fillUp( vector<vector<bool>>& dp, int r, int c, int k, bool val ) {
        int R = r+k, C = c+k;
        for( int r1=r; r1<R; r1++ )
            for( int c1 = c; c1<C; c1++ ) 
                dp[r1][c1] = val;
    }
    
    void computeRes( int r, int c, int& res, int curRes, vector<vector<bool>>& dp ) {
        int R = dp.size(), C = dp.front().size();
        if( curRes >= res )
            return;
        if( c >= C ) {       //  The condition should be c>=C, as we are skipping k cells as a part of optimisation-2.
            computeRes( r+1, 0, res, curRes, dp );
            return;
        }
        if( r == R ) {
            res = min( res, curRes );
            return;
        }
        if( dp[r][c] ) {
            while( c<C and dp[r][c] )   c++;    // Optimisation-1: Skip all the cells which are already filled.
            computeRes( r, c, res, curRes, dp );
            return;
        }
        for( int k=min(R-r,C-c); k>0; k-- ) {
            if( not isAvailable( dp, r, c, k ) )
                break;
            fillUp( dp, r, c, k, true );
            computeRes( r, c+k, res, curRes+1, dp );     // Optimisation-2: use c+k, instead of c+1
            fillUp( dp, r, c, k, false );
        }
    }
public:
    int tilingRectangle(int R, int C) {
        int res = INT_MAX, curRes = 0;
        vector< vector<bool> > dp( R, vector<bool>(C,false) );
        computeRes( 0, 0, res, curRes, dp );
        return res;
    }
};
