class Solution {
public:
    int dp[50000][2];
    int calc(vector<int>&ar,int i,bool turn){
        if(i>=ar.size())
            return 0;
        int n=ar.size();
        if(dp[i][turn]!=-1) return dp[i][turn];
        int ans1=0,ans2=0;
        if(turn){
            int sum=0;
            ans1=INT_MIN;
            for(int j=i;j<i+3&&j<n;j++){
                 sum+=ar[j];
                ans1=max(ans1,sum+calc(ar,j+1,false));
            }
        }
        else{
            ans2=INT_MAX;
             int sum=0;
             for(int j=i;j<i+3&&j<n;j++){
                   sum-=ar[j];
                ans2=min(ans2,sum+calc(ar,j+1,true));
            }
        }
        return dp[i][turn]=ans1+ans2;
        
    }
    string stoneGameIII(vector<int>& stoneValue) {
         memset(dp,-1,sizeof(dp));
        int x=calc(stoneValue,0,true);       
        if(x<0)
            return "Bob";
         if(x>0)
            return "Alice";        
       return "Tie";
    }
};
/*
    0-> ALice +ve 
    1-> Bob   -ve
*/
