class Solution {
public:
    static const int N = 2e5+1;
    
    int parent[N];
    Solution(){
        for(int i = 0 ;i < N ; i++) parent[i] = i;
    }
    int find(int u){
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    void join(int u,int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        parent[v] = parent[u];
    }
    bool swappable(int u,int v){
        u = find(u);
        v = find(v);
        return (u == v);
    }
    bool gcdSort(vector<int>& nums) {
        int n = nums.size();
        vector<int> a(nums);
        sort(begin(a),end(a));
        unordered_set<int> st;
        for(int &i : a){
            for(int j = 2; j*j <= i; j++){
                if(i%j == 0){
                    if(j*j != i){
                        join(i,i/j);
                    }
                    join(i,j);
                }
            }
            st.insert(i);
        }
        for(int i = 0 ; i < n ; i++){
            if(!swappable(a[i],nums[i])) return false; 
        }
        return true;
    }
};
