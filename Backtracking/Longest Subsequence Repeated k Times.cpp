class Solution {
public:
    int alphabet=26;
    bool find(string &s, string &temp, int k)
    {
        int j=0;
        int n= s.length();
        int count=0;
        for(int i=0;i<n;i++){
            if(s[i]==temp[j]){
                j++;
                if(j==temp.size()){
                    count++;
                    j=0;
                }
                if(count==k){
                    return true;
                }
            }
        }
        return false;
    }
    string longestSubsequenceRepeatedK(string s, int k) {
        int n= s.length();
        queue<string>q;
        q.push("");
        //string temp="";
        string ans="";
        while(!q.empty()){
            string curr= q.front();
            q.pop();

            for(int i=0;i<alphabet;i++){
                string temp= curr + char('a'+i);
                if(find(s,temp,k)){
                    ans= temp;
                    q.push(temp);
                }
            }
        }
        return ans;

    }
};
