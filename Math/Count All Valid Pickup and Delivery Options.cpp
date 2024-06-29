class Solution {
public:
   #define m1 1000000007
   #define ll long long
   const ll N=1001;
ll fact[1002];
ll modInv[1002];
ll pow_1(ll base,ll x){
    if(x<0) return 0;
    ll ans=1;
    while(x){
    if(x&1){
       ans=(ans*base)%m1;
       x--;
    }
    else{
      base=(base*base)%m1;
      x=x/2;
    }
    }
    return ans;
}
void precomp(){
    fact[0]=1;
    modInv[0]=1;
    for(ll i=1;i<=N;i++){
        fact[i]=(fact[i-1]*i)%m1;
        modInv[i]=pow_1(fact[i],m1-2);
    }
}

ll ncr(ll n,ll r){
    if(r>n) return 0;
    ll numo=fact[n];
    ll demo=(modInv[r]*modInv[n-r])%m1;
   
    ll ans=(numo*demo)%m1;
    return ans; 
}
    int countOrders(int n) {
        precomp();
        ll ans=1;
        for(int i=2*n;i>2;i-=2){
             ans*=ncr(i,2);
             ans=(ans%m1);
        }
        return ans;
    }
};
