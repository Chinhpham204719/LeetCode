class Solution {
public:
    vector<int> v; // vector storing the upper limit for each digit place
    int dp[(1<<10)][11][2][2];
    int dfs(int d, int mask, bool flag, bool s){
        if(d<=0)return 1;
        if(dp[mask][d][flag][s]!=-1)return dp[mask][d][flag][s];
        int ans = 0;
        for(int i = 0; i<=9; i++){
            if(!i){
                if(s&&((mask&(1<<i))==0)){} // if a non-zero element is present and we already have zero then we do nothing
                else if(s){ //but if we don't have zero we take zero and change mask
                    if(flag||(i<v[v.size()-d])){
                        ans += dfs(d-1, (mask^(1<<i)), 1, 1);
                    }
                    else ans += dfs(d-1, (mask^(1<<i)), 0, 1);
                }
                else{
                    if(flag||(i<v[v.size()-d])){  //if not started and not have zero, then take zero without changing mask
                        ans += dfs(d-1, mask, 1, 0);
                    }
                    else ans += dfs(d-1, mask, 0, 0);
                }
            }
            else if(mask&(1<<i)){
                if(flag||(i<v[v.size()-d]))
                ans += dfs(d-1, (mask^(1<<i)), 1, 1);
                else if(i==v[v.size()-d]) ans += dfs(d-1, (mask^(1<<i)), 0, 1);
            }
        }
        return dp[mask][d][flag][s] = ans;
    }
    
    int countSpecialNumbers(int n) {
        int d = log10(n)+1;
        while(n){
            v.push_back(n%10);
            n = n/10;
        }
        reverse(v.begin(), v.end());
        int mask = (1<<10)-1;
        memset(dp, -1, sizeof(dp));
        return dfs(d,mask, 0, 0)-1; // -1 as to remove 0 as it is not part of the range [1,n]
    }
};
