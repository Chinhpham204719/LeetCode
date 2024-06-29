class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int cnt = 0;
        for(int i = 0 ; i < arr.size() ; i++) if(arr[i] == 1) cnt++;
        if(cnt % 3 != 0) return {-1, -1};
        if(cnt == 0) return {0, 2};

        int k = cnt / 3, curr = 0;
        int i1 = -1, i2 = -1, i3 = -1;
        int j1 = -1, j2 = -1, j3 = -1;

        for(int i = 0 ; i < arr.size() ; i++)
        {
            if(arr[i] == 1)
            {
                curr++;
                if(curr == 1) i1 = i;
                if(curr == k + 1) i2 = i;
                if(curr == 2*k + 1) i3 = i;

                if(curr == k) j1 = i;
                if(curr == 2*k) j2 = i;
                if(curr == 3*k) j3 = i;
            }
        }
        vector < int > a, b, c;
        copy(arr.begin() + i1, arr.begin() + j1 + 1, back_inserter(a));
        copy(arr.begin() + i2, arr.begin() + j2 + 1, back_inserter(b));
        copy(arr.begin() + i3, arr.begin() + j3 + 1, back_inserter(c));

        if(a != b || a != c) return {-1, -1};

        int first = 0, second = 0, third = 0;
        first = i2 - j1 - 1;
        second = i3 - j2 - 1;
        third = arr.size() - j3 - 1;

        if(third > min(first, second)) return {-1, -1};
        
        return {j1 + third, j2 + third + 1};
    }
};
