class Solution {
public:
    long long beautifulSubstrings(string s, int k) {
        int v=0,c=0;
        vector<int> pre;
        pre.push_back(0); // Since initially vowels=0 and consonants=0
        long long int n=s.size(),ans=0;
        for(auto x:s){
            if(x=='a' || x=='e' || x=='i' || x=='o' || x=='u'){
                v++;
            }
            else{
                c++;
            }
            pre.push_back(v-c);
        }
        unordered_map<int,vector<int>> mpp;
        for(int i=0;i<=n;i++){
            int diff=pre[i];
            if(mpp.find(diff)!=mpp.end()){
                for(auto x:mpp[diff]){
                    long long int t=(i-x)/2; //numbers of vowels= half the length of substrings as no. of vowels= no. of consonants
                    if((t*t)%k==0){
                        ans++;
                    }
                    //checking t%k==0 does not work because k may have a factor which is a perfect for eg: t=2 and k=4
                }
            }
            mpp[diff].push_back(i);
        }
        return ans;
    }
};
