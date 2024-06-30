class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        int g = 0;
        for(auto &i: numsDivide){
            g = __gcd(g,i);//gcd of numsDivide
        }
        priority_queue<int,vector<int>,greater<int>> pq;//creater a queue get minimum element of nums
        for(auto &i: nums){
            pq.push(i);
        }
        int x = 0;
        while(!pq.empty() && g%pq.top()){//run untill i cann't get an element for that g divide by minimum element nums.
            x++;
            pq.pop();
        }
        if(pq.empty())return -1;//if queue empty there is no element who divide all element of numDivide
        return x;
    }
};
