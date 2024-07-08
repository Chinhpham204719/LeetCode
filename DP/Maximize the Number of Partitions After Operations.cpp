#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <climits>

using namespace std;

vector<int> helper(vector<vector<int>>& nxt, int x, int y, int oc, int cc) {
    vector<int> v;
    for (int i = 0; i < 26; i++) {
        if (i != oc && i != cc) {
            if (nxt[x][i] != -1) v.push_back(nxt[x][i]);
        } else {
            if (oc == cc) v.push_back(nxt[x][i]);
            else if (i == oc) {
                if (nxt[x][i] < y) v.push_back(nxt[x][i]);
                else {
                    int tt = (y == nxt.size() - 1) ? -1 : nxt[y + 1][i];
                    if (tt != -1) v.push_back(tt);
                }
            } else {
                if (nxt[x][i] != -1 && nxt[x][i] < y) v.push_back(nxt[x][i]);
                else v.push_back(y);
            }
        }
    }
    sort(v.begin(), v.end());
    return v;
}

// Hàm chính
int maxPartitionsAfterOperations(string s, int k) {
    if (k == 26) return 1;
    int n = s.size();
    vector<vector<int>> nxt(n, vector<int>(26, -1));
    vector<int> f(n), pos(n);
    
    // Điền nxt
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 1) {
            for (int j = 0; j < 26; j++) {
                nxt[i][j] = nxt[i + 1][j];
            }
        }
        nxt[i][s[i] - 'a'] = i;
    }

    // Điền f và pos
    for (int i = n - 1; i >= 0; i--) {
        vector<int> v;
        for (int j = 0; j < 26; j++) {
            if (nxt[i][j] != -1) v.push_back(nxt[i][j]);
        }
        sort(v.begin(), v.end());
        if (v.size() <= k) {
            f[i] = 1;
            pos[i] = n - 1;
        } else {
            f[i] = 1 + f[v[k]];
            pos[i] = v[k] - 1;
        }
    }

    // Tìm số lượng phân đoạn tối đa
    int ret = 1;
    int cur = 0;
    int mask = 0;
    for (int i = 0; i < n; i++) {
        int r = pos[i];
        int curmask = 0;
        for (int j = i; j <= r; j++) {
            curmask |= (1 << (s[j] - 'a'));
            for (int c = 0; c < 26; c++) {
                if ((j == i) && (mask & (1 << c))) continue;
                auto v = helper(nxt, i, j, s[j] - 'a', c);
                if (v.size() <= k) ret = max(ret, cur + 1);
                else {
                    int pp = v[k];
                    if (pp > j) ret = max(ret, cur + 1 + f[pp]);
                    else {
                        auto vv = helper(nxt, j, j, s[j] - 'a', c);
                        if (vv.size() <= k) ret = max(ret, (j > i) + cur + 1);
                        else ret = max(ret, (j > i) + cur + 1 + f[vv[k]]);
                    }
                }
            }
        }
        i = r;
        cur++;
        mask = curmask;
    }
    return ret;
}

int main() {
    string s = "abcde";
    int k = 2;
    cout << "Maximum Partitions After Operations: " << maxPartitionsAfterOperations(s, k) << endl;
    return 0;
}
