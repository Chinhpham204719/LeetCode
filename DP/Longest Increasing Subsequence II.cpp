class Solution {
public:
    int find(int x,vector<int>&par)
    {
        if(x==par[x])
        {
            return x;
        }
        return par[x]=find(par[x],par);
    }
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int n=grid.size(),m=grid[0].size();
        if(n==1 and m==1)
        {
            return 1;
        }
        queue<pair<int,int>>q;
        q.push({0,0});
        vector<vector<int>>par_r(n,vector<int>(m+1,0)),par_c(m,vector<int>(n+1,0));
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=m;j++)
            {
                par_r[i][j]=j;
            }
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<=n;j++)
            {
                par_c[i][j]=j;
            }
        }
        int cnt=2;
        while(!q.empty())
        {
            int sz=q.size();
            for(int k=0;k<sz;k++)
            {
                auto [x,y]=q.front();
                q.pop();
                int j=find(par_r[x][y+1],par_r[x]);
                while(j<m and j<=grid[x][y]+y)
                {
                    if(x==n-1 and j==m-1)
                    {
                        return cnt;
                    }
                    q.push({x,j});
                    par_r[x][j]=j+1;
                    j=find(par_r[x][j],par_r[x]);
                }
                int i=find(par_c[y][x+1],par_c[y]);
                while(i<n and i<=grid[x][y]+x)
                {
                    if(i==n-1 and y==m-1)
                    {
                        return cnt;
                    }
                    q.push({i,y});
                    par_c[y][i]=i+1;
                    i=find(par_c[y][i],par_c[y]);
                }
            }
            cnt++;
        }
        return -1;
    }
};
