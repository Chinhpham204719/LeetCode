struct Cycle {
    unordered_map<int, int> node_to_idx;
    vector<int> idx_to_node;
    vector<long long> pre;
};

class Solution {
    vector<int> next;
    long long k;
    int n;
    
    vector<int> color;
    int cycle_end;
    vector<Cycle> cycles;
    vector<int> node_to_cycle;
    
    void dfs(int v) {
        if (color[v] == 2) {
            return;
        } else if (color[v] == 1) {
            cycle_end = v;
            cycles.emplace_back();
            node_to_cycle[v] = cycles.size() - 1;
            return;
        }
        
        color[v] = 1;
        
        dfs(next[v]);
        
        if (cycle_end != -1) {
            int cycle_idx = node_to_cycle[cycle_end];
            Cycle& cycle = cycles[cycle_idx];
            cycle.idx_to_node.push_back(v);
            node_to_cycle[v] = node_to_cycle[cycle_end];
            
            if (v == cycle_end) {
                reverse(cycle.idx_to_node.begin(), cycle.idx_to_node.end());
                for (int i = 0; i < cycle.idx_to_node.size(); ++i) {
                    cycle.node_to_idx[cycle.idx_to_node[i]] = i;
                }
                cycle_end = -1;
            }
        }
        
        color[v] = 2;
    }
    
    vector<bool> is_source;
    
    long long sum_on_cycle(int start, long long steps) {
        int cycle_id = node_to_cycle[start];
        Cycle& cycle = cycles[cycle_id];
        int cycle_size = cycle.node_to_idx.size();
        long long sum = (steps / cycle_size) * cycle.pre[cycle_size] +  cycle.pre[cycle.node_to_idx[start] + 1 + (steps % cycle_size)] - cycle.pre[cycle.node_to_idx[start] + 1];
        return sum;
    }
    
    int next_node_on_cycle(int start, long long steps) {
        int cycle_id = node_to_cycle[start];
        Cycle& cycle = cycles[cycle_id];
        int cycle_size = cycle.node_to_idx.size();
        return cycle.idx_to_node[(cycle.node_to_idx[start] + steps) % cycle_size];
    }
    
    long long solve() {
        n = next.size();
        
        node_to_cycle.resize(n, -1);
        
        color.resize(n, 0);
        cycle_end = -1;
        for (int i = 0; i < n; ++i) {
            dfs(i);
        }
        
        for (Cycle& cycle : cycles) {
            int num_nodes = cycle.node_to_idx.size();
            cycle.pre.push_back(0);
            for (int j = 0; j < 3; ++j) {
                for (int i = 0; i < num_nodes; ++i) {
                    cycle.pre.push_back(cycle.pre.back() + cycle.idx_to_node[i]);
                }    
            }
        }
        
        is_source.resize(n, true);
        for (int i = 0; i < n; ++i) {
            is_source[next[i]] = false;
        }
        
        long long ans = 0;
        
        for (Cycle& cycle : cycles) {
            int cycle_size = cycle.idx_to_node.size();
            long long sum = (long long)cycle.idx_to_node[0] + sum_on_cycle(cycle.idx_to_node[0], k);
            ans = max(ans, sum);
            
            int slow = cycle.idx_to_node[0];
            int fast = next_node_on_cycle(slow, k + 1);
            for (int i = 0; i < cycle_size; ++i) {
                sum = sum + fast - slow;
                ans = max(ans, sum);
                fast = next[fast];
                slow = next[slow];
            }
        }
        
        
        for (int i = 0; i < n; ++i) {
            if (is_source[i]) {
                long long sum = 0;
                
                int fast = i;
                for (long long j = 0; j <= k; ++j) {
                    sum += fast;
                    if (node_to_cycle[fast] != -1) {
                        sum += sum_on_cycle(fast, k - j);
                        fast = next_node_on_cycle(fast, k - j + 1);
                        break;
                    }
                    fast = next[fast];
                }
                ans = max(ans, sum);

                int slow = i;
                while (node_to_cycle[slow] == -1) {
                    sum = sum + fast - slow;
                    ans = max(ans, sum);
                    fast = next[fast];
                    slow = next[slow];
                }
            }
        }
        
        return ans;
    }
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {
        next.swap(receiver);
        this->k = k;
        return solve();
    }
};Maximize Value of Function in a Ball Passing Game
