class Solution
{
public:
    class DisjointSet
    {
    public:
        vector<int> rank, parent, size;

        DisjointSet(int n)
        {
            rank.resize(n + 1, 0);
            parent.resize(n + 1);
            size.resize(n + 1, 1);
            for (int i = 0; i <= n; i++)
            {
                parent[i] = i;
            }
        }

        int find_Ultimate_parent(int node)
        {
            if (node == parent[node])
            {
                return node;
            }
            return parent[node] = find_Ultimate_parent(parent[node]);
        }

        void Union_By_Rank(int u, int v)
        {
            int ulp_u = find_Ultimate_parent(u);
            int ulp_v = find_Ultimate_parent(v);
            if (ulp_u == ulp_v)
            {
                return;
            }

            if (rank[ulp_u] < rank[ulp_v])
            {
                parent[ulp_u] = ulp_v;
            }
            else if (rank[ulp_v] < rank[ulp_u])
            {
                parent[ulp_v] = ulp_u;
            }
            else
            {
                parent[ulp_v] = ulp_u;
                rank[ulp_u]++;
            }
        }

        void Union_By_Size(int u, int v)
        {
            int ulp_u = find_Ultimate_parent(u);
            int ulp_v = find_Ultimate_parent(v);
            if (ulp_u == ulp_v)
            {
                return;
            }

            if (size[ulp_u] < size[ulp_v])
            {
                parent[ulp_u] = ulp_v;
                size[ulp_v] += size[ulp_u];
            }
            else
            {
                parent[ulp_v] = ulp_u;
                size[ulp_u] += size[ulp_v];
            }
        }
    };

    vector<bool> areConnected(int n, int threshold, vector<vector<int>> &queries)
    {
        DisjointSet ds(n);
        vector<bool> ans;

        for(int i = threshold + 1; i <= n; i++)
        {
            for(int j = i; j <= n; j += i)
            {
                ds.Union_By_Rank(i, j);
            }
        }

        for (auto it : queries)
        {
            int u = it[0];
            int v = it[1];

            if (ds.parent[u] == ds.parent[v])
            {
                ans.push_back(true);
            }
            else
            {
                ans.push_back(false);
            }
        }

        return ans;
    }
};
